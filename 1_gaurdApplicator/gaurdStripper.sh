for f in $(find ./include/ -type f); do 
	fileStr=$(cat "$f");
	#remove ifndef/define
	gaurdRemoved=$(tail -n +2 "$f"); 
	#remove endif
	strippedText=$(tail n +1 "$f"); 
	echo "$strippedText" > $f; 
done

