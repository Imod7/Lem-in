import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


def get_paths_from_string(file_name):
    i = 0
    with open(file_name, 'r') as file:
        file_lines = file.readlines()
        # Iterate over the lines
        for line in file_lines:
            line = line.strip()
            print("line : ", line)
            # print(line.strip())
        # data = data.replace('\n', '')
        # you may also want to remove whitespace characters like `\n` at the end of each line
            if i == 0:
                all_rooms = line.split(" -> ")
                # print("start ", all_rooms)
                # print()
            else:
                all = line.split(" -> ")
                all = all[::-1]
                all_rooms.extend(all)
                # print("next ", all)
                # print()
            # print()
            i += 1
    return (all_rooms)

file_name = "files/paths_in"
all_rooms = get_paths_from_string(file_name)
print("all rooms from all paths \n", all_rooms)

str0 = "Xqj8 -> Hvd5 -> Dfw1 -> Axa3 -> Fub8 -> Yps0 -> E_y2 -> I_q8 -> Yee0 -> Nef9 -> Qyu5 -> Q_m8 -> Azi0 -> Csx5"
rooms = str0.split(" -> ")
print(rooms)

def update_line(num, data, line):
    # print(data)
    # print(data[..., :num])
    # print(num)
    line.set_data(data[..., :num])
    # line.set_data(3, 7)
    return line,

fig1 = plt.figure()

# Fixing random state for reproducibility
# np.random.seed(19680801)

xs = np.arange(0,11,1)
ys = np.random.normal(loc=3, scale=0.9, size=11)
print("xs", xs)
print("xy", ys)

# 'bo-' means blue color, round points, solid lines
plt.plot(xs,ys,'bo-')

# zip joins x and y coordinates in pairs
for x,y,r in zip(xs,ys, rooms):

    label = r

    plt.annotate(label, # this is the text
                 (x,y), # this is the point to label
                 textcoords="offset points", # how to position the text
                 xytext=(0,10), # distance from text to points (x,y)
                 ha='center') # horizontal alignment can be left, right or center

plt.xticks(np.arange(0,10,1))
plt.yticks(np.arange(0,7,0.5))

# data = np.random.rand(2, 45)
# print(data)

# data = np.array([[3,22,11],[3,1,6]])
data = np.array([xs, ys])
print(data)
# data = np.array([0.14022471,  0.96360618, 0.37601032,  0.25528411])
l, = plt.plot([], [], 'r-')
# plt.plot(23, 11)
plt.xlim(-1, 18)
plt.ylim(0, 7)
plt.xlabel('x')
plt.title('test')
line_ani = animation.FuncAnimation(fig1, update_line, 300, fargs=(data, l),
                                   interval=300, blit=True)


plt.show()