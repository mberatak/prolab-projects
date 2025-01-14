import pandas as pd
import ast
import re
import dash
from dash import dcc, html
import dash_cytoscape as cyto
from dash.dependencies import Input, Output


excel_dosya_yolu = "prolab3data.xlsx"


df = pd.read_excel(excel_dosya_yolu)

def normalize_author_name(name):
    
    name = name.lower()
    name = re.sub(r'[.\s]+', ' ', name)  
    return name.strip()

def temizle_ve_parse_veri(df):
    
    author_to_id = {}
    makaleler = {}
    temizlenmis_veriler = []

    for index, row in df.iterrows():
        makale_adi = row['paper_title']
        
        
        coauthors_str = row['coauthors']
        
        
        if coauthors_str and coauthors_str.startswith('['):
            try:
               yazarlar = [normalize_author_name(yazar) for yazar in ast.literal_eval(coauthors_str)]
            except (ValueError, SyntaxError):
              
                yazarlar = [normalize_author_name(yazar) for yazar in coauthors_str.replace('[', '').replace(']', '').split(',')]

        elif coauthors_str:
          yazarlar = [normalize_author_name(yazar) for yazar in coauthors_str.split(',')]

        else:
            yazarlar = []
            
        doi = row.get('doi', 'Bilinmiyor') 
        
        
        makaleler[doi] = {
            'title':makale_adi,
            'authors':yazarlar,
            'doi': doi
        }

        temizlenmis_veriler.append({
        'title':makale_adi,
        'authors': yazarlar,
        'doi': doi
        })

    return temizlenmis_veriler, author_to_id, makaleler


temizlenmis_veriler, author_to_id, makaleler = temizle_ve_parse_veri(df)

class Graph:
    def __init__(self):
        self.nodes = {}  
        self.edges = {}  

    def add_node(self, node_name):
      if node_name not in self.nodes:
            self.nodes[node_name] = node_name

    def add_edge(self, node1_name, node2_name, weight):
      edge = (node1_name, node2_name)
      if edge not in self.edges and (node2_name, node1_name) not in self.edges :
        self.edges[edge] = weight
      elif edge in self.edges:
            self.edges[edge] += weight
      elif (node2_name, node1_name) in self.edges:
            self.edges[(node2_name, node1_name)] += weight
    
    def get_node_name(self, node_name):
      return self.nodes.get(node_name, None)
    
    def get_edge_weight(self, node1_name, node2_name):
        edge1 = (node1_name, node2_name)
        edge2 = (node2_name, node1_name)
        if edge1 in self.edges:
            return self.edges[edge1]
        elif edge2 in self.edges:
            return self.edges[edge2]
        else:
           return 0
    def get_number_of_nodes(self):
        return len(self.nodes)

    def get_number_of_edges(self):
        return len(self.edges)

    
def create_graph(temizlenmis_veriler, author_to_id):
   
    graph = Graph()
    unique_authors = set()  
    for row in temizlenmis_veriler:
        for yazar in row['authors']:
            unique_authors.add(yazar) 
    for yazar in unique_authors:
        graph.add_node(yazar)
    for row in temizlenmis_veriler:
        yazarlar = row['authors']
        if len(yazarlar) > 0:  
             first_author = yazarlar[0] 
             for i in range(1, len(yazarlar)): 
                graph.add_edge(first_author, yazarlar[i], 1) 
           
    return graph

graph = create_graph(temizlenmis_veriler, author_to_id)


def create_cytoscape_elements(graph, author_to_id, makaleler):
    
    elements = []
    main_authors = set()  

   
    author_article_counts = {}
    for author in graph.nodes:
       author_article_counts[author] = 0
       for doi, makale in makaleler.items():
             if author in makale['authors']:
                  author_article_counts[author] += 1
                  
    
    total_articles = sum(author_article_counts.values())
    average_articles = total_articles / len(author_article_counts) if author_article_counts else 0

   
    for node_name in graph.nodes.keys():
        is_main = any(edge[0] == node_name or edge[1] == node_name for edge in graph.edges)
        
         
        article_count = author_article_counts.get(node_name, 0)
        
         
        size = 25  # varsayılan değer
        color = 'lightgray'  # varsayılan değer

        if article_count > average_articles * 1.2:  # ortalamanın %20 fazlası ise
          size = 50
          color = 'darkblue'
        elif article_count < average_articles * 0.8: # ortalamanın %20 azı ise
           size = 10
           color= 'lightblue'
        else: # ortalamaya yakın ise
            size = 15
            color='lightblue'
        
        elements.append({
             "data": {"id": node_name, "label": node_name},
             "classes": "main-author" if is_main else "co-author",
             "style": {"width": size, "height": size, "background-color": color}
         })
        if is_main:
            main_authors.add(node_name)


    
    for (node1_name, node2_name), weight in graph.edges.items():
          if (node1_name in main_authors or node2_name in main_authors):
            elements.append({"data": {"source": node1_name, "target": node2_name, "weight": weight}})
    return elements


cytoscape_elements = create_cytoscape_elements(graph, author_to_id, makaleler)

def get_author_articles(author_name, makaleler):
    """Verilen yazara ait makaleleri getirir."""
    author_articles = []
    for doi, makale in makaleler.items():
        if author_name in makale['authors']:
              author_articles.append(makale)
    return author_articles

def bfs_shortest_path(graph, start_node_name, end_node_name):
    """Belirtilen başlangıç ve bitiş düğümleri arasında BFS kullanarak en kısa yolu bulur."""
    queue = [(start_node_name, 0, None)]  
    visited = set()  
    distances = {start_node_name: 0}  
    previous_nodes = {}  

    while queue:  
        current_node_name, distance, previous_node = queue.pop(0)  

        if current_node_name == end_node_name:  
            
            path = []  
            while current_node_name is not None:  
                path.insert(0, current_node_name)  
                current_node_name = previous_nodes.get(current_node_name)  
            return path, distances, previous_nodes  

        if current_node_name in visited:  
            continue
        visited.add(current_node_name)  

        for neighbor_node_name, weight in graph.edges.items():  
            if neighbor_node_name[0] == current_node_name:  
                if neighbor_node_name[1] not in distances:  
                    distances[neighbor_node_name[1]] = distance + 1  
                    previous_nodes[neighbor_node_name[1]] = current_node_name  
                    queue.append((neighbor_node_name[1], distance + 1, current_node_name))  
            elif neighbor_node_name[1] == current_node_name:  
                if neighbor_node_name[0] not in distances:  
                    distances[neighbor_node_name[0]] = distance + 1 
                    previous_nodes[neighbor_node_name[0]] = current_node_name  
                    queue.append((neighbor_node_name[0], distance + 1, current_node_name)) 
    return None, None, None  


def print_shortest_path(graph, start_author_name, end_author_name):
    """En kısa yolu bulur ve yazdırır."""
    path, distances, previous_nodes = bfs_shortest_path(graph, start_author_name, end_author_name)
    if path:  
        print("En kısa yol: ", " -> ".join(path))
        print("Yol üzerindeki yazarlar: ", path)
        print("Mesafeler: ", distances)
        print("Önceki Düğümler: ", previous_nodes)
        return "En kısa yol: " + " -> ".join(path) + "<br>" + "Yol üzerindeki yazarlar: " + ", ".join(path)
    else:
        return "Yol bulunamadı"

def update_shortest_path(graph, start_author_name, end_author_name):
    return print_shortest_path(graph, start_author_name, end_author_name)

def create_weighted_queue(graph, start_node_name):
        
        weighted_authors = []
        for edge, weight in graph.edges.items():
           if edge[0] == start_node_name:
               author_name = edge[1]
               author_weight = 0
               for second_edge, second_weight in graph.edges.items():
                   if second_edge[0] == author_name or second_edge[1] == author_name:
                        author_weight += 1
               weighted_authors.append((author_name, author_weight))
           elif edge[1] == start_node_name:
               author_name = edge[0]
               author_weight = 0
               for second_edge, second_weight in graph.edges.items():
                   if second_edge[0] == author_name or second_edge[1] == author_name:
                        author_weight += 1
               weighted_authors.append((author_name, author_weight))
        
        weighted_authors.sort(key=lambda x: x[1], reverse=True)
        return [author_name for author_name, _ in weighted_authors]

def print_queue(graph, start_node_name):
        queue = create_weighted_queue(graph, start_node_name)
        print("Kuyruk: ")
        for item in queue:
            print(f"Yazar: {item}", end=", ")
        print("")
        return "Kuyruk: " + ", ".join([item for item in queue])

def update_queue(graph, start_author_name):
      return print_queue(graph, start_author_name)


class BSTNode:
        
        def __init__(self, value):
            
            self.value = value
            self.left = None
            self.right = None

class BST:
       
        def __init__(self):
            
            self.root = None

        def insert(self, value):
           
            if not self.root:
                self.root = BSTNode(value)
            else:
                self._insert_recursive(self.root, value)

        def _insert_recursive(self, node, value):
         
           if value < node.value:
                if node.left:
                    self._insert_recursive(node.left, value)
                else:
                    node.left = BSTNode(value)
           else:
                if node.right:
                    self._insert_recursive(node.right, value)
                else:
                    node.right = BSTNode(value)

        def delete(self, value):
         
           self.root = self._delete_recursive(self.root, value)
        
        def _delete_recursive(self, node, value):
          
            if not node:
                 return node
            if value < node.value:
                 node.left = self._delete_recursive(node.left, value)
            elif value > node.value:
                 node.right = self._delete_recursive(node.right, value)
            else:
                if not node.left:
                    return node.right
                elif not node.right:
                     return node.left
                node.value = self._min_value_node(node.right).value
                node.right = self._delete_recursive(node.right, node.value)
            return node
        
        def _min_value_node(self, node):
            
            current = node
            while current.left:
                current = current.left
            return current
        
        def to_list(self):
           
            result = []
            self._to_list_recursive(self.root, result)
            return result
        
        def _to_list_recursive(self, node, result):
         
           if node:
              self._to_list_recursive(node.left, result)
              result.append(node.value)
              self._to_list_recursive(node.right, result)
def print_bst(graph, start_author_name, delete_author_name):
      
      queue = create_weighted_queue(graph, start_author_name)  
      bst = BST() 
      for author_name in queue: 
          bst.insert(author_name) 
      
      print("BST (Başlangıç): ", bst.to_list())
      bst.delete(delete_author_name)
      print("BST (Son Durum): ",  bst.to_list())
      return "BST (Başlangıç): " + ", ".join(bst.to_list()) + "<br>" + "BST (Son Durum): " + ", ".join(bst.to_list())

def update_bst(graph, start_author_name, delete_author_name):
        return print_bst(graph, author_to_id, start_author_name, delete_author_name)

def bfs_shortest_path_for_all(graph, start_node_name):
    
    queue = [(start_node_name, 0, None)] 
    visited = set() 
    distances = {start_node_name: 0} 
    previous_nodes = {} 

    while queue: 
        current_node_name, distance, previous_node = queue.pop(0) 
          
        if current_node_name in visited: 
             continue
        visited.add(current_node_name) 

        for neighbor_node_name, weight in graph.edges.items():
             if neighbor_node_name[0] == current_node_name:  
                  if neighbor_node_name[1] not in distances: 
                       distances[neighbor_node_name[1]] = distance + 1  
                       previous_nodes[neighbor_node_name[1]] = current_node_name 
                       queue.append((neighbor_node_name[1], distance + 1, current_node_name)) 
             elif neighbor_node_name[1] == current_node_name: 
                  if neighbor_node_name[0] not in distances:  
                      distances[neighbor_node_name[0]] = distance + 1 
                      previous_nodes[neighbor_node_name[0]] = current_node_name 
                      queue.append((neighbor_node_name[0], distance + 1, current_node_name))
    return distances, previous_nodes 
def print_all_shortest_paths(graph, start_node_name):
      """Tüm en kısa yolları hesaplar ve yazdırır."""
      distances, previous_nodes = bfs_shortest_path_for_all(graph, start_node_name) 
      results = "En kısa yollar: <br>"
      for end_node_name, distance in distances.items(): 
          if end_node_name != start_node_name: 
              path = []
              current_node_name = end_node_name
              while current_node_name is not None:
                  path.insert(0, current_node_name)
                  current_node_name = previous_nodes.get(current_node_name)
              results += f"({start_node_name} -> {end_node_name}) : Mesafe: {distance}, Yol:  {' -> '.join(path)} <br>"
      print(results)
      return results
def update_all_shortest_paths(graph, start_author_name):
       return print_all_shortest_paths(graph, start_author_name)


def count_collaborators(graph, start_node_name):
        
        collaborators = set()
        for edge, weight in graph.edges.items():
            if edge[0] == start_node_name:
                collaborators.add(edge[1])
            elif edge[1] == start_node_name:
                 collaborators.add(edge[0])
        return len(collaborators)

def print_collaborator_count(graph, start_node_name):
        
        count = count_collaborators(graph, start_node_name)
        print(f"İşbirliği yaptığı yazar sayısı: {count}")
        return f"İşbirliği yaptığı yazar sayısı: {count}"
def update_collaborator_count(graph, start_author_name):
     return print_collaborator_count(graph, start_author_name)

def find_most_collaborative_author(graph):
   
    max_collaborations = 0
    most_collaborative_author = None
    for author_name in graph.nodes:
            count = count_collaborators(graph, author_name)
            if count > max_collaborations:
                 max_collaborations = count
                 most_collaborative_author = author_name
    return most_collaborative_author, max_collaborations

def print_most_collaborative_author(graph):
       
       author_name, max_count = find_most_collaborative_author(graph)
       print(f"En çok işbirliği yapmış yazar: {author_name}, işbirliği sayısı: {max_count}")
       return f"En çok işbirliği yapmış yazar: {author_name}, işbirliği sayısı: {max_count}"
def update_most_collaborative_author(graph):
      return print_most_collaborative_author(graph)

def dfs_longest_path(graph, start_node_name, visited, current_path, longest_path):
   """Derinlik öncelikli arama ile en uzun yolu bulur."""
   visited.add(start_node_name) 
   current_path.append(start_node_name)  
   
   if len(current_path) > len(longest_path[0]):
         longest_path[0] = current_path[:]

   for neighbor_name, weight in graph.edges.items():
      if neighbor_name[0] == start_node_name and neighbor_name[1] not in visited: 
         dfs_longest_path(graph, neighbor_name[1], visited, current_path, longest_path) 
      elif neighbor_name[1] == start_node_name and neighbor_name[0] not in visited: 
          dfs_longest_path(graph, neighbor_name[0], visited, current_path, longest_path) 

   current_path.pop() 
   visited.remove(start_node_name) 


def find_longest_path(graph, start_node_name):
     
     visited = set()
     longest_path = [[]]
     current_path = []
     dfs_longest_path(graph, start_node_name, visited, current_path, longest_path)
     return longest_path[0]

def print_longest_path(graph, start_node_name):
    path = find_longest_path(graph, start_node_name)
    print(f"En uzun yol: {' -> '.join(path)}, Uzunluk: {len(path) - 1 if len(path) > 0 else 0}")
    return f"En uzun yol: {' -> '.join(path)}, Uzunluk: {len(path) - 1 if len(path) > 0 else 0}"

def update_longest_path(graph, start_author_name):
      return print_longest_path(graph, start_author_name)

app = dash.Dash(__name__)
app.layout = html.Div([
    html.H1("Yazar İşbirliği Ağı Analizi"),
    cyto.Cytoscape(
        id='cytoscape-graph',
        elements=cytoscape_elements,
        layout={'name': 'cose', 'idealEdgeLength': 150, 'nodeOverlap': 40, 'padding': 40},
         style={'width': '100%', 'height': '500px'}
    ),
    html.Div(id='author-articles-output'),
     html.Div([
      html.Label("İster 1: Başlangıç Yazar Adı"),
      dcc.Input(id='start-author-name-1', type='text', value="Ramya Cheramangalath Balan"),
      html.Label("Bitiş Yazar Adı"),
      dcc.Input(id='end-author-name-1', type='text', value="B. Rajakumar"),
      html.Button('En Kısa Yolu Bul', id='shortest-path-button', n_clicks=0),
       html.Div(id='output-shortest-path')
    ]),
    html.Div([
         html.Label("İster 2: Başlangıç Yazar Adı"),
         dcc.Input(id='start-author-name-2', type='text', value="Ramya Cheramangalath Balan"),
         html.Button('Kuyruğu Oluştur', id='queue-button', n_clicks=0),
         html.Div(id='output-queue')
    ]),
     html.Div([
         html.Label("İster 3: Başlangıç Yazar Adı"),
         dcc.Input(id='start-author-name-3', type='text', value="Ramya Cheramangalath Balan"),
         html.Label("Silinecek Yazar Adı"),
          dcc.Input(id='delete-author-name-3', type='text', value="B. Rajakumar"),
         html.Button('BST Oluştur ve Sil', id='bst-button', n_clicks=0),
         html.Div(id='output-bst')
     ]),
    html.Div([
         html.Label("İster 4: Başlangıç Yazar Adı"),
         dcc.Input(id='start-author-name-4', type='text', value="Ramya Cheramangalath Balan"),
         html.Button('Tüm En Kısa Yolları Bul', id='all-shortest-paths-button', n_clicks=0),
         html.Div(id='output-all-shortest-paths')
     ]),
    html.Div([
         html.Label("İster 5: Başlangıç Yazar Adı"),
        dcc.Input(id='start-author-name-5', type='text', value="Ramya Cheramangalath Balan"),
        html.Button('İşbirliği Yapan Yazar Sayısını Bul', id='collaborator-count-button', n_clicks=0),
         html.Div(id='output-collaborator-count')
     ]),
     html.Div([
          html.Button('En Çok İşbirliği Yapan Yazarı Bul', id='most-collaborative-button', n_clicks=0),
          html.Div(id='output-most-collaborative')
      ]),
   html.Div([
        html.Label("İster 7: Başlangıç Yazar Adı"),
        dcc.Input(id='start-author-name-7', type='text', value="Ramya Cheramangalath Balan"),
        html.Button('En Uzun Yolu Bul', id='longest-path-button', n_clicks=0),
        html.Div(id='output-longest-path')
    ])
])
@app.callback(
    Output('author-articles-output', 'children'),
    Input('cytoscape-graph', 'tapNodeData')
)
def display_author_articles(node_data):
    if node_data:
      author_name = node_data['label']
      author_articles = get_author_articles(author_name, makaleler)
      if author_articles:
        return html.Div([
                html.H3(f"{author_name} tarafından yayınlanan makaleler:"),
                html.Ul([html.Li(f"{article['title']} (DOI: {article.get('doi', 'Bilinmiyor')})") for article in author_articles])
        ])
      else:
        return html.Div("Bu yazara ait makale bulunamadı.")
    else:
        return html.Div("Lütfen bir düğüme tıklayın.")

@app.callback(
       Output('output-shortest-path', 'children'),
       Input('shortest-path-button', 'n_clicks'),
       Input('start-author-name-1', 'value'),
       Input('end-author-name-1', 'value'),

    )
def update_shortest_path_callback(n_clicks, start_author_name, end_author_name):
       if n_clicks > 0:
         return update_shortest_path(graph, start_author_name, end_author_name)
@app.callback(
        Output('output-queue', 'children'),
        Input('queue-button', 'n_clicks'),
        Input('start-author-name-2', 'value')
    )
def update_queue_callback(n_clicks, start_author_name):
       if n_clicks > 0:
        return update_queue(graph, start_author_name)
@app.callback(
    Output('output-bst', 'children'),
    Input('bst-button', 'n_clicks'),
     Input('start-author-name-3', 'value'),
     Input('delete-author-name-3', 'value')
)
def update_bst_callback(n_clicks, start_author_name, delete_author_name):
     if n_clicks > 0:
        return update_bst(graph, author_to_id, start_author_name, delete_author_name)

@app.callback(
    Output('output-all-shortest-paths', 'children'),
    Input('all-shortest-paths-button', 'n_clicks'),
     Input('start-author-name-4', 'value')
)
def update_all_shortest_paths_callback(n_clicks, start_author_name):
     if n_clicks > 0:
        return update_all_shortest_paths(graph, author_to_id, start_author_name)

@app.callback(
    Output('output-collaborator-count', 'children'),
    Input('collaborator-count-button', 'n_clicks'),
     Input('start-author-name-5', 'value')
)
def update_collaborator_count_callback(n_clicks, start_author_name):
     if n_clicks > 0:
        return update_collaborator_count(graph, start_author_name)

@app.callback(
    Output('output-most-collaborative', 'children'),
    Input('most-collaborative-button', 'n_clicks')
)
def update_most_collaborative_author_callback(n_clicks):
     if n_clicks > 0:
          return update_most_collaborative_author(graph)

@app.callback(
    Output('output-longest-path', 'children'),
    Input('longest-path-button', 'n_clicks'),
     Input('start-author-name-7', 'value')
)
def update_longest_path_callback(n_clicks, start_author_name):
     if n_clicks > 0:
       return update_longest_path(graph, start_author_name)

if __name__ == '__main__':
    app.run_server(debug=True)