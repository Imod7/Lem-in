RED="\x1b[38;2;227;66;52m"
BLUE="\x1b[38;2;40;177;249m"
GREEN="\x1b[38;2;80;200;120m"
YELLOW="\x1b[38;2;253;253;150m"
STOP="\e[0m"

# for file in testmaps/*; do
#     echo "$(basename "$file")"
# done
# in the file output, it finds the empty line and puts the text
# result=`awk '$0=($0)?$0:"HERE IT IS"' output`
echo "Would you like to generate new maps? [y/n]"
read run_generator

# we are calling the generate_maps script if the answer given above is yes
if [ "$run_generator" = "y" ]
then
  echo "How many maps per category would you like to generate?"
  read maps_amount_per_cat
  sh ./generate_maps.sh $maps_amount_per_cat
fi

# we get all the files from the testmaps folder
FILES="testmaps/*"

tests_passed=0
tests_failed=0
flow_one=0
flow_ten=0
flow_thousand=0
big=0
big_super=0
# For each file we do all the actions in the for loop
for f in $FILES;
do
  printf $BLUE
  file=$(basename "$f")
  printf "File: $file $STOP \t\t -> "
  # wc="$(./push_swap $line | wc -l)"

  # Counting how many maps from each category I am testing
  if [ ${file:0:7} == "flow-on" ]
  then 
    let flow_one++
  elif [ ${file:0:7} == "flow-te" ]
  then
    let flow_ten++
  elif [ ${file:0:7} == "flow-th" ]
  then
    let flow_thousand++
  elif [ ${file:0:7} == "big-sup" ]
  then
    let big_super++
  elif [ ${file:0:3} == "big" ] && [ ${file:3:7} != "-supe" ]
  then
    let big++
  fi

  # Running the lem-in executable and saving it to output
  output="$(./lem-in < $f > output)"

  # If the verifier file is present then run it 
  if [ -e verifier ]
  then
      verifier="$(./lem-in < $f | ./verifier)"
      verifier=`expr $verifier + 0`
      # echo "result of verifier : '"$verifier"'"
  fi

  # search="Lines Needed"
  # result=`grep "$search" output | cut -d ":" -f2 | tr -d '[:space:]'`

  # Here we are counting the number of lines our executable is doing 
  # to move the ants by starting to count lines after the first empty line
  # we encounter
  result=`sed '1,/^$/d' output | wc -l`
  dom=`expr $result + 0`

  # Here we find the number of lines mentioned in the map
  search="lines required"
  result=`grep "$search" $f | head -1 | cut -d ":" -f2 | tr -d '[:space:]'`
  gen=`expr $result + 0`

  printf "You: "$dom" VS Gen: "$gen

  # Here we compare the number of lines our lemin is making ($dom)
  # with the number of lines required ($gen) and we increase 
  # the corresponding counter if our lines are more/equal/less 
  # than the required lines
  if [ "$dom" -lt "$gen" ] && [ "$dom" -ne 0 ]
  then
    if [ -e verifier ] && [ "$dom" -eq "$verifier" ]
    then
      printf "$GREEN \t [ PASS SUPER ] $RESET\n"
      let tests_passed++
    elif [ -e verifier ] && [ "$dom" -ne "$verifier" ]
    then
      printf "$RED \t [ FAIL ] $RESET\n"
      let tests_passed++
    fi
  elif [ "$dom" -eq "$gen" ]
  then
    if [ -e verifier ] && [ "$dom" -eq "$verifier" ]
    then
      printf "$GREEN \t [ PASS ] $RESET\n"
      let tests_passed++
    elif [ -e verifier ] && [ "$dom" -ne "$verifier" ]
    then
      printf "$RED \t [ FAIL ] $RESET\n"
      let tests_passed++
    fi
  else
    printf "$RED \t [ FAIL ] $RESET\n"
    let tests_failed++
  fi
done

echo "Do you want to delete all generated maps? [y/n]"
read response

if [ "$response" = "y" ]
then
  # delete all generated maps in the folder testmaps
  `rm testmaps/*`
fi

#  When we processed all files we can print the results below
printf $YELLOW
printf "FINAL RESULTS\n"
printf "=============\n"
printf $STOP
printf $GREEN 
printf "Tests Passed : $tests_passed $RESET\n"
printf $RED
printf "Tests Failed : $tests_failed $RESET\n"
printf $STOP
printf $BLUE 
printf " Tests run for flow-one : $flow_one\n"
printf " Tests run for flow-ten : $flow_ten\n"
printf " Tests run for flow-thousand : $flow_thousand\n"
printf " Tests run for big : $big\n"
printf " Tests run for big-superposition : $big_super\n"
