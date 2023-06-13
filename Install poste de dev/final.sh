#!/usr/bin/env bash
text=$1
url=$2

# for each file in the folder ./Ressources_client_Photos-20221212
for photo in ./Ressources_client_Photos-20221212/*; do
    # remove .svg
    photo=${photo%.*}
    # get the last 3 characters
    photo=${photo: -3}
    # create the command
    docker container run -ti --rm -v $url:/work sae103-imagick "magick $photo.svg -grayscale Rec709Luminance -crop 600x550+0+0 -resize 200x200 $photo.png"
done

res=$(egrep -i code=fr-[a-z]{3} < ./Ressources_client_Textes-20221212/{$text} | cut -d'=' -f2)

docker container run -ti -v $url:/work bigpapoo/sae103-qrcode qrencode -o code.png "https://bigbrain.biz/$res"
docker container run -ti --rm -v $url:/work bigpapoo/sae103-php php -f ./script/final.php $text $url $res