import sys
import matplotlib.pyplot as plt
import networkx as nx
import path_functions as pf
import ants_functions as af

TGREEN =  '\033[32m' # Green Text
TYELLOW =  '\033[33m' # Yellow Text
TWHITE = '\033[37m' # White Text
ENDC = '\033[m' # reset to the defaults

def main(argv):
    G = nx.Graph()
    color_map = []

    file_name = argv
    ants_ids = af.get_ants_ids(file_name)
    pos_y = 3

    print(TYELLOW + "Paths used by the ants in BFS" + ENDC)
    path_id = 1
    paths_amount = len(ants_ids)
    for ant in ants_ids:
        ant = ant + "-"
        # print(ant)
        print("Path id : ", path_id)
        path = pf.get_path(file_name, ant)
        print(path)
        pf.add_path(G, path, pos_y, paths_amount)
        pos_y = pos_y + 10
        path_id += 1
        # if i == 3:
        #     break
        # i += 1

    pos = nx.get_node_attributes(G, 'pos')
    fig = plt.figure()
    nx.draw(G, pos, node_color='skyblue', with_labels = True, node_size=1100, edge_color='white')
    fig.set_facecolor("#24292E")
    plt.show()
    pass

if __name__ == "__main__":
    main(sys.argv[1])