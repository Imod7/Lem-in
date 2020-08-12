printf "Generating maps "

counter=1
while [ $counter -le $1 ]
do
	filename="flow-one${counter}"
	# echo $filename
	gen="$(./generator --flow-one > testmaps/$filename)"

	filename="flow-ten${counter}"
	# echo $filename
	gen="$(./generator --flow-ten > testmaps/$filename)"

	filename="flow-thousand${counter}"
	# echo $filename
	gen="$(./generator --flow-thousand > testmaps/$filename)"

	filename="big${counter}"
	# echo $filename
	gen="$(./generator --big > testmaps/$filename)"

	printf "."

	filename="big-superposition${counter}"
	# echo $filename
	gen="$(./generator --big-superposition > testmaps/$filename)"

	printf "."

  	((counter++))
done

printf "\nAll maps were generated successfully\n"