for f in $(find ./include/ -type f); do 
	fileStr=$(cat "$f"); 
	fileName=${$f:9};
	gaurdName=$(tr "$filename" / _)^^
	echo '#ifndef '"$gaurdName"'_INCLUDED' > $f
	echo '#define '"$gaurdName"'_INCLUDED' >> $f
	echo "$fileStr" >> $f; 
	echo -e "\n\n#endif" >> $f;
	#cat ./0_licenceApplicator/LICENCE_insert > $f;
	echo "$fileStr" >> $f; 
done
