<?php

$url = 'http://itgd-mum-dev-static.s3.ap-south-1.amazonaws.com/s3fs-public/crop_image/goof-up-story_647_02281708083639661488302961.jpeg';
echo firebase_short_url($url);


/*
 * Set the Firebase API Configuration 
 * 
 */

function firebase_config(){
    $firebase = array(
        'api-key' => 'AIzaSyDjXq0vdDZaa4HgEsdrlfLWXjevvIw7FFk',
        'dynamicLinkDomain' => 'peg3z.app.goo.gl',
        'androidPackageName' => 'com.indiatoday',
        'iosBundleId' => 'com.dci.indiatoday',
    );
    return $firebase;
}



function firebase_short_url($url){
 
//get Default values  from config
$fire_base = firebase_config();    
$fire_base_url = 'https://firebasedynamiclinks.googleapis.com/v1/shortLinks?key='.$fire_base['api-key'].'';    
$base_config = '{
  "dynamicLinkInfo": {
    "dynamicLinkDomain": "'.$fire_base['dynamicLinkDomain'].'",
    "link": "'.$url.'",
    "androidInfo": {
      "androidPackageName": "'.$fire_base['androidPackageName'].'",
    },
    "iosInfo": {
      "iosBundleId": "'.$fire_base['iosBundleId'].'",
    }
  }
}';

$curl = curl_init();
curl_setopt($curl, CURLOPT_URL, $fire_base_url);
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: text/plain'));
curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($curl, CURLOPT_POSTFIELDS, $base_config);
$result = curl_exec($curl);
curl_close($curl);
$final_result = json_decode($result);
return $final_result->shortLink;
}


?>
