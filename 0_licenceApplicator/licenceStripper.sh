cat ./LICENCE > ./0_licenceApplicator/LICENCE_insert
echo -e "\n\n\n" >> ./0_licenceApplicator/LICENCE_insert

numLines=$(wc -l < 0_licenceApplicator/LICENCE_insert)
numLines=$((numLines+1))

for f in $(find ./include/ -type f); do 
	fileStr=$(cat "$f");
	strippedText=$(tail -n +"$numLines" "$f"); 
	echo "$strippedText" > $f; 
done

