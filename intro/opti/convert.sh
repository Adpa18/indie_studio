for entry in "."/*
do
  echo "$entry"
  convert $entry -gravity center -background black -extent 1024x512 $entry
done
