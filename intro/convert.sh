echo "Convert png to jpg..."
mogrify -format jpg *.png
echo "DONE"
for entry in "."/*.jpg
do
  echo "convert $entry to 1024x512"
  convert $entry -gravity center -background black -extent 1024x512 $entry
done
echo "DONE"
