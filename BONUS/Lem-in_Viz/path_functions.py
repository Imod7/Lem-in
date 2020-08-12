#  Functions to re-create the paths that the ants followed
#  by checking the result file (output) of Lem-in


# Function to check if I have a common room between two paths

def common_data(path_a, path_b): 
    result = False
    for a in path_a: 
        for b in path_b:
            if a == b: 
                print("room ", a, " == room ", b)
                result = True
                return result   
    return result 


#  In function get_path we follow the path that the given ant_id 
#  has followed in every line of the output and we return that path

def get_path(file, ant_id):
	f = open(file, 'r') 
	lines = f.readlines()
	count = 0
	flag = 0
	# print("ant_id : ", ant_id)
	lenroom = len(ant_id)
	path = []
	for line in lines:
		count += 1
        # print("Line{}: {}".format(count, line.strip()))
		if (flag == 1) and (ant_id in line):
            # print("Line :", count)
			index1 = line.find(ant_id)
			index = line.find(ant_id) + len(ant_id)
			room = line[index:]
			room = room.partition(" ")[0].strip()
			# print("room ", room, "\nline ", line[index1:])
			path.append(room)
            # print(line.split("L2-",1)[1])
            # exit()
		if len(line.strip()) == 0:
            # print("empty Line{}: {}".format(count, line.strip()))
			flag = 1
	return (path)

# In function add_path we add the path found in the given graph G
# and in specific x and y positions

def add_path(G, path, pos_y, paths_amount):
    i = 0
    pos_x = 1
    # print(path)
    while i < len(path):
        if i == len(path) - 1:
            G.add_node(path[i], pos=(pos_x, paths_amount))
        else:
            G.add_node(path[i], pos=(pos_x, pos_y))
        if i != 0:
            G.add_edge(path[i], path[i - 1])
        i += 1
        if (i % 2 == 0):
            pos_y += 5
        else:
            pos_y -= 5
        pos_x += 4

# def add_path_to_graph(G, filename, ant_id, pos_y, paths_amount):
# 	path = get_path(ant_id, filename)
# 	return (path)
    # print("bfs \n", path)
    # dfs_str = "Xqj8 -> Qku1 -> Wrx8 -> Dga6 -> Cmd2 -> Hma8 -> Nlb2 -> Clk6 -> G_v3 -> Xnd6 -> Sgx1 -> Hvp1 -> Ghr8 -> I_q4 -> Ky_7 -> Pi_2 -> Xny9 -> Sfm0 -> Rxn5 -> Xq_4 -> Qar4 -> Dxb5 -> Fw_2 -> Fyk1 -> Zhz4 -> Vfu6 -> Oo_4 -> Ugw0 -> I_w8 -> Ugl1 -> Xsc3 -> Emg7 -> Sky2 -> Gfu0 -> Feb5 -> Qlg5 -> Qyi4 -> Dzm1 -> Dis9 -> Psh7 -> Csw7 -> Pon7 -> Kbh1 -> Hsn2 -> Jcg0 -> Tv_2 -> Mgt2 -> Zdr4 -> Dsi8 -> K_c7 -> Tyv0 -> Ndr9 -> Zhm2 -> Qat9 -> Gzp9 -> Cif4 -> Aub1 -> Yl_4 -> Ojt0 -> Fkb5 -> Ryb1 -> T_p4 -> Xhq5 -> Jlr1 -> Hqg5 -> Pbb6 -> Axd2 -> Iol4 -> Msx1 -> Wks4 -> Mbx1 -> Iou6"
    # dfs = dfs_str.split(" -> ")
    # print("dfs \n", dfs)
    # print("Does dfs exist in bfs ?\n")
    # print("RESULT = ", common_data(dfs, path))
    # print(TWHITE + "Ant id ", path_id, " is in path \n" + TGREEN, path, ", size : ", len(path), "\n" + ENDC)
	