# Function to check the first line of the ants move lines
# from the result (output file) of Lem-in
# and make a list with all the ant_ids in that line.
# That way we can retrace all paths that are used in 
# moving the ants

def get_ants_ids(file_name):
    f = open(file_name, 'r') 
    lines = f.readlines()
    ants_ids = []
    for line in lines:
        if line.startswith("L1-"):
            # print("Line {}".format(line.strip()))
            x = line.split()
            # print("x ", x)
            for items in x:
                items = items.split('-')
                # print(items[0])
                ants_ids.append(items[0])
            break
    return (ants_ids)
    # print("ants_ids\n", ants_ids)