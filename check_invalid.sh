RED="\x1b[38;2;227;66;52m"
BLUE="\x1b[38;2;40;177;249m"
GREEN="\x1b[38;2;80;200;120m"
YELLOW="\x1b[38;2;253;253;150m"
STOP="\e[0m"

# we get all the files from the testmaps folder
FILES="Ultimate_Lem-in_test/*"

counter=0
# For each file in the folder specified above 
# we do all the actions in the for loop
for f in $FILES;
do
  let counter++
  printf $BLUE
  file=$(basename "$f")
  printf "$counter File: $file $STOP \t\t -> "
  output="$(./lem-in < $f > output)"
  line=$(head -n 1 output)
  result=`cat output | wc -l`
  # sleep .5
  if [ "$result" -gt 1 ]
  then
    printf "$RED CHECK IT OUT!!! $RESET"
    printf "\n"
  # elif [ "$result" -eq 0 ]
  # then
  #   printf "\n"
  fi
done
