arr=($(ls $1));
let i=1
for file in ${arr[@]}; do
    echo "$file $i"
    djpeg -bmp $1/$file > $2/$i.bmp
    let i=i+1
done