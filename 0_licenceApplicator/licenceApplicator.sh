echo -e "/*\n" > ./0_licenceApplicator/LICENCE_insert
cat ./LICENCE >> ./0_licenceApplicator/LICENCE_insert
echo -e "\n*/" >> ./0_licenceApplicator/LICENCE_insert
echo -e "\n\n\n" >> ./0_licenceApplicator/LICENCE_insert

for f in $(find ./include/ -type f); do 
	fileStr=$(cat "$f"); 
	cat ./0_licenceApplicator/LICENCE_insert > $f;  
	echo "$fileStr" >> $f; 
done
