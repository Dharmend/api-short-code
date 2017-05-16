<?php
/*
 *  About theming cck fields ,,
 * we can theme any cck field view templates as a tpl file suppose field name is 'field_image' in article content type
 *  than we can put these types of tpl files in theme folder
 *  
 *  1- field--field-name--content-type.tpl.php
    2- field--content-type.tpl.php
    3- field--field-name.tpl.php
    4- field--field-type.tpl.php
 * 
 * 
 * Available variables in field templates :
 * 
$items : an array containg the values of the field.
$items[n]['view'] contains the ready-to-use, filtered, formatted value
$label : the label of the field
$label_display : the display settings for the label ('hidden', 'above', or 'inline')
$field_empty : TRUE if there is nothing to display in the field
$field_type : the type of the field,
$field_name : the name of the field,
$field_type_css : same as above, with '-' signs replaced with '_' for use in css properties
$field_name_css : same as above, with '-' signs replaced with '_' for use in css properties
$field : an array containing the full CCK field object
 * 
 * 
 * for more reference visit:
 * https://www.drupal.org/node/1089656

 * 
 */
?>
<div style="color: red">
<?php
echo "Start field theming drupal 7";?>
</div>
<?php    
//print_r($items);
//print(render($items[n]['view']));

?>




