echo "Lisiting files in directory"
ls
echo -e "\n description of files"
for file in *; do
     if [ -f "$file" ];then
     echo -n "file:- $file|"
     echo -n "type: $(file -b "$file")|"
     fi
done