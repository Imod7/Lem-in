## Prerequisites
1. Copy in this folder your lem-in executable and the generator script

## How to run
1. Run the run script with the following command :
```
$ ./run.sh
```
2. You will be asked to give the number of maps you want to generate per category (flow-one, flow-ten, flow-thousand, big and big-superposition)
3. All maps are generated and saved in the testmaps folder 
4. Then each map is tested with your lem-in executable and prints if you passed the test (less or equal lines as the map requires) or failed (more lines than the map requires)
5. When all maps are tested, you are asked if you wish to keep the generated maps in the testmaps folder or delete them
6. At the end, the final results are shown at the end when the execution is completed


### A screenshot from the Lem-in-Tester
![lemin_tester](/images/lemin_test.png)

