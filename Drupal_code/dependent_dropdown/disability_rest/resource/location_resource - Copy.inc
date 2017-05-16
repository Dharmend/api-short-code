<?php

$str = 'mocmobileapp';
$security = md5($str);
define("SECURE",$security);
$security_token = constant("SECURE");
//623e7eaa15922bdee56be2033f797386

function register_update_devices($data){
   // echo 'Comming request with POST Methods';
$security_token = constant("SECURE");

    if($data['plateform'] != '' && $data['notification_token'] && $data['device_id'] && $data['token']){
        
	$plateform = $data['plateform'];
        $notification_token = $data['notification_token'];
        $device_id = $data['device_id'];
        $token = $data['token'];
	
        if($security_token == $data['token']){
            
     
        $check_query = db_select('custom_register_devices','c')
                        ->fields('c',array('device_id'))
                        ->condition('c.device_id',$device_id)
                        ->execute();
        if($check_query->rowCount() >0){
            //device is already register
            
            $up_qry = db_update('custom_register_devices')
                        ->fields(array(
                            'plateform' => $plateform,
                            'notification_token' => $notification_token,
                            'token' => $token,
                        ))
                        ->condition('device_id',$device_id)
                        ->execute();
            
            
            $msg = 'Device is already register';
            $res = array('_resultflag' => 0,'message' => $msg);
            return services_error($msg, 200, $res);
                
            //return services_error('Device not registered.', 406);
        }else{
            //registe this device
            
            $register = db_insert('custom_register_devices')
                    ->fields(array(
                      'plateform' => $plateform,
                      'notification_token' => $notification_token,
                      'device_id' => $device_id,
                      'token' => $token,
                    ))
                    ->execute();
            if(isset($register)){
                
                $msg = 'Device successfully registered.';
                $res = array('_resultflag' => 1,'message' => $msg);
                return services_error($msg, 200,$res);
                
                
            }
        }
    }else{ //security Check
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
        
    }
}

function city_listing($data){
    
    $security_token = constant("SECURE");
    $token = $data['token'];
    
    if($security_token == $token){
        
        $city_qry = db_select('node','n')
                    ->fields('n',array('nid','title'))
                    ->condition('n.type','city')
                    ->condition('n.status',1)
                    ->execute();
        
        $city_list = array();
        $total_cities = $city_qry->rowCount();
        if($city_qry->rowCount() >0){
            
            foreach ($city_qry as $qry){
                
                $city_list['id'] = $qry->nid;
                $city_list['name'] = $qry->title;
                $allcity_list[] = $city_list;
                
            }
            
            
        $msg = '';
        $res = array('_resultflag' => 1,'_totalcount' => $total_cities, 'cities' => $allcity_list);
        return services_error($msg, 200, $res);
            
        }else{
            
        $msg = 'No Record Found.';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
            
        }
        
    }else{
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
    
    
}


function eventsubcategory_listing($data){
    
    $security_token = constant("SECURE");
    
    $parent_cat = $data['category_name'];
    $token = $data['token'];
    //$index = $data['index'];
    $total_record = $data['totalrecord'];
    
    $add = 0;
    $index = ($data['index'] > 0) ? $data['index'].''.$add :  $data['index'];
    
    if($security_token == $token){
        
        
        //find total counts
        
//         $catqry = db_select('field_data_field_parent_category','cat');
//            $catqry->innerJoin('node','n','n.nid = cat.entity_id');
//            $catqry->fields('n',array('nid','title'));
//            $catqry->condition('n.status',1);
//            if($parent_cat != ''){
//            $catqry->condition('cat.field_parent_category_value',$parent_cat);
//            }
//            $catqry->condition('cat.bundle','event_subcategory');
//            $categ_total_count = $catqry->execute();
//            
//            $total_subcat = $categ_total_count->rowCount();
        //end of the code
        
            $catqry = db_select('field_data_field_parent_category','cat');
            $catqry->innerJoin('node','n','n.nid = cat.entity_id');
            $catqry->fields('n',array('nid','title'));
            $catqry->condition('n.status',1);
            if($parent_cat != ''){
            $catqry->condition('cat.field_parent_category_value',$parent_cat);
            }
            $catqry->condition('cat.bundle','event_subcategory');
//            if($index != '' && $total_record != ''){
//                $catqry->range($index,$total_record);
//            }
            $catqry->orderBy('n.title','ASC');
            $categ = $catqry->execute();

            $all_subcat_list = array();
            $total_subcat = $categ->rowCount();
            
            if($categ->rowCount() > 0){
                foreach ($categ as $c){
                    
                    $data_qry = db_select('field_data_field_event_subcategory','sbc')
                                ->fields('sbc', array('entity_id'))
                                ->condition('sbc.field_event_subcategory_nid',$c->nid)
                                ->execute();
                    if($data_qry->rowCount() >0){

                    $all_subcat_list['id'] = $c->nid;
                    $all_subcat_list['name'] = $c->title;
                    
                    
                    }
                    
                    $allsub[] = $all_subcat_list; 

                }
                
        $msg = '';
        $res = array('_resultflag' => 1,'_totalcount' => $total_subcat, 'subcat_listing' => $allsub);
        return services_error($msg, 200, $res);
                
        }  else {
        
        $msg = 'No Record Found.';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
            
        }
            
            
        
    }else{
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
    
    
}

function event_listing($data){
   
    $security_token = constant("SECURE");
    $token = $data['token'];
    
    if($token == $security_token){
    
       
    $parent_cat = $data['category'];
    $sub_cat = $data['sub_category'];
    $city = $data['city'];
    $organization = $data['organization'];
    $venue = $data['venue'];
    $fdate = $data['date'];
    $tdate = $data['date'];
    
    //$index = $data['index'];
    $total_record = $data['totalrecord'];
    
    $add = 0;
    $index = ($data['index'] > 0) ? $data['index'].''.$add :  $data['index'];
    
    
//    $rdate = '2014-07-19';
//    $cdate = '2014-07-19';
    
 //find total count
    
    
    $event_qry = db_select('node','n');
    $event_qry->fields('n',array('nid','title'));
    $event_qry->condition('n.type','event_calendar');
    $event_qry->condition('n.status',1);
    if($parent_cat != ''){
        $event_qry->innerJoin('field_data_field_event_category','cat','cat.entity_id = n.nid');
        $event_qry->condition('cat.field_event_category_value',$parent_cat);
    }
    if($sub_cat != ''){
        $event_qry->innerJoin('field_data_field_event_subcategory','subcat','subcat.entity_id = n.nid');
        $event_qry->condition('subcat.field_event_subcategory_nid',$sub_cat);
    }
    if($city != ''){
        $event_qry->innerJoin('field_data_field_event_city','city','city.entity_id = n.nid');
        $event_qry->condition('city.field_event_city_nid',$city);

    }
    if($organization != ''){
        $event_qry->innerJoin('field_data_field_event_organization','org','org.entity_id = n.nid');
        $event_qry->condition('org.field_event_organization_nid',$organization);

    }
    if($venue != ''){
        
        $event_qry->innerJoin('field_data_field_venue','v','v.entity_id = n.nid');
        $event_qry->condition('v.field_venue_value','%' . db_like($venue) . '%', 'LIKE');
        
    }
    if($fdate != '' && $tdate){
        $event_qry->innerJoin('field_data_event_calendar_date','rdate','rdate.entity_id = n.nid');
        $event_qry->condition('rdate.event_calendar_date_value', array($fdate, $tdate),'BETWEEN');//>=
    }
    //if($cdate != ''){
    //    $event_qry->innerJoin('field_data_field_custom_schedule','cdate','cdate.entity_id = n.nid');
    //    $event_qry->condition('cdate.field_custom_schedule_value',$cdate);
    //}
    
    $event_qry->orderBy('n.nid', 'DESC');


$total_count_query = $event_qry->execute();
$total_events = $total_count_query->rowCount();    
    
    
 //end of the code   
    


    $event_qry = db_select('node','n');
    $event_qry->fields('n',array('nid','title'));
    $event_qry->condition('n.type','event_calendar');
    $event_qry->condition('n.status',1);
    if($parent_cat != ''){
        $event_qry->innerJoin('field_data_field_event_category','cat','cat.entity_id = n.nid');
        $event_qry->condition('cat.field_event_category_value',$parent_cat);
    }
    if($sub_cat != ''){
        $event_qry->innerJoin('field_data_field_event_subcategory','subcat','subcat.entity_id = n.nid');
        $event_qry->condition('subcat.field_event_subcategory_nid',$sub_cat);
    }
    if($city != ''){
        $event_qry->innerJoin('field_data_field_event_city','city','city.entity_id = n.nid');
        $event_qry->condition('city.field_event_city_nid',$city);

    }
    if($organization != ''){
        $event_qry->innerJoin('field_data_field_event_organization','org','org.entity_id = n.nid');
        $event_qry->condition('org.field_event_organization_nid',$organization);

    }
    if($venue != ''){
        
        $event_qry->innerJoin('field_data_field_venue','v','v.entity_id = n.nid');
        $event_qry->condition('v.field_venue_value','%' . db_like($venue) . '%', 'LIKE');
        
    }
    if($fdate != '' && $tdate){
        $event_qry->innerJoin('field_data_event_calendar_date','rdate','rdate.entity_id = n.nid');
        $event_qry->condition('rdate.event_calendar_date_value', array($fdate, $tdate),'BETWEEN');//>=
    }
    //if($cdate != ''){
    //    $event_qry->innerJoin('field_data_field_custom_schedule','cdate','cdate.entity_id = n.nid');
    //    $event_qry->condition('cdate.field_custom_schedule_value',$cdate);
    //}
    
    if($index != '' && $total_record != ''){
       $event_qry->range($index,$total_record);
     }
     $event_qry->orderBy('n.nid', 'DESC');


$query = $event_qry->execute();

$event_list = array();

//$total_events = $query->rowCount();

if($query->rowCount() >0){
    
    foreach ($query as $eq){
     
        $event_detail = node_load($eq->nid);
        
        $event_list['id'] = isset($event_detail->nid) ? $event_detail->nid : '';
        $event_list['name'] = isset($event_detail->title) ? $event_detail->title : '';
        $find_key = locale_language_list();
        
        $lang_list = array();
        if(!empty($event_detail->field_language_listing['und'])){
                foreach ($event_detail->field_language_listing['und'] as $l){
                    
                    $lang_list[] = $l['value'];
                }
               $language = implode(',', $lang_list);
        }else{
            $language = isset($event_detail->language) ? $find_key[$event_detail->language] : '';
        }
        
        $event_list['language'] = $language;
        $event_list['description'] = isset($event_detail->body['und'][0]['value']) ? $event_detail->body['und'][0]['value'] : '';
        $city = node_load($event_detail->field_event_city['und'][0]['nid']);
        $event_list['city'] = isset($event_detail->field_event_city['und'][0]['nid']) ? $city->title : '';
        
        $org = node_load($event_detail->field_event_organization['und'][0]['nid']);
        $event_list['organization'] = isset($event_detail->field_event_organization['und'][0]['nid']) ? $org->title : '';
        
        $event_list['category'] = isset($event_detail->field_event_category['und'][0]['value']) ? $event_detail->field_event_category['und'][0]['value'] : '';
        
        $subcat = node_load($event_detail->field_event_subcategory['und'][0]['nid']);
        $event_list['subcategory'] = isset($event_detail->field_event_subcategory['und'][0]['nid']) ? $subcat->title : '';
        $event_list['contact_no'] = isset($event_detail->field_contact_number['und'][0]['value']) ? $event_detail->field_contact_number['und'][0]['value'] : '';
       
        $event_list['event_entry'] = isset($event_detail->field_event_entry['und'][0]['value']) ? $event_detail->field_event_entry['und'][0]['value'] : '';
        $event_list['fee_india'] = isset($event_detail->field_fee_india['und'][0]['value']) ? $event_detail->field_fee_india['und'][0]['value'] : '';
        $event_list['fee_foreign'] = isset($event_detail->field_fee_foreign['und'][0]['value']) ? $event_detail->field_fee_foreign['und'][0]['value'] : '';
        $event_list['entry_criteria'] = isset($event_detail->field_entry_criteria['und'][0]['value']) ? $event_detail->field_entry_criteria['und'][0]['value'] : '';
       
        $event_list['venue'] = isset($event_detail->field_venue['und'][0]['value']) ? $event_detail->field_venue['und'][0]['value'] : '';
        
        $person = array();
        $persons = array();
        
    foreach ($event_detail->field_person_type['und'] as $p){
        $person['By'] = $p['field_by']['und'][0]['value'];
        $person['person_name'] = $p['field_name_of_person']['und'][0]['value'];
        $persons[] = $person;
    }
    
    $event_list['by_whom'] = (!empty($persons)) ? $persons : array();
    
   
    $event_list['lat'] = isset($event_detail->field_map_address['und'][0]['lat']) ? $event_detail->field_map_address['und'][0]['lat'] : '';
    $event_list['lng'] = isset($event_detail->field_map_address['und'][0]['lng']) ? $event_detail->field_map_address['und'][0]['lng'] : '';
    
    if($event_detail->event_calendar_date['und'][0]['value'] != '' && $event_detail->event_calendar_date['und'][0]['value2'] != ''){
        $event_list['from_date'] = isset($event_detail->event_calendar_date['und'][0]['value']) ? date('d-m-Y', strtotime($event_detail->event_calendar_date['und'][0]['value'])) : '';
        $event_list['end_date'] = isset($event_detail->event_calendar_date['und'][0]['value2']) ? date('d-m-Y', strtotime($event_detail->event_calendar_date['und'][0]['value2'])) : '';
    }  else {
    
        $event_list['from_date'] = isset($event_detail->field_custom_schedule['und'][0]['value']) ? date('d-m-Y',  strtotime($event_detail->field_custom_schedule['und'][0]['value'])): '';
        $event_list['end_date'] = '';//in custom date end date is not available,
    }
    $event_time = array();
    $e_time = array();
    
    foreach ($event_detail->field_time['und'] as $t){
        
        $st1 = strlen($t['field_event_start_time']['und'][0]['value'] > 1) ? $t['field_event_start_time']['und'][0]['value'] : '0'.$t['field_event_start_time']['und'][0]['value'];
        $st2 = strlen($t['field_event_start_minutes']['und'][0]['value'] > 1) ? $t['field_event_start_minutes']['und'][0]['value'] : '0'.$t['field_event_start_minutes']['und'][0]['value'];
        
        $end1 = strlen($t['field_event_end_time_hr']['und'][0]['value'] > 1) ? $t['field_event_end_time_hr']['und'][0]['value'] : '0'.$t['field_event_end_time_hr']['und'][0]['value'];
        $end2 = strlen($t['field_enent_end_time_minuetes']['und'][0]['value'] > 1) ? $t['field_enent_end_time_minuetes']['und'][0]['value'] : '0'.$t['field_enent_end_time_minuetes']['und'][0]['value'];
        
        $min1 = strlen($st2) > 1 ? $st2 : '0'.$st2;
        $min2 = strlen($end2) > 1 ? $end2 : '0'.$end2;
        
        $min0 = strlen($st1) > 1 ? $st1 : '0'.$st1;
        $end0 = strlen($end1) > 1 ? $end1 : '0'.$end1;
        
        $e_time['Event_start_time'] = $min0.':'.$min1;
        $e_time['Event_end_time'] = $end0.':'.$min2;
        $event_time[] = $e_time;
    }
    
    $event_list['event_time'] = (!empty($event_time)) ? $event_time : array();
    
    
     //images
    
    $event_images = array();
    $bFileExists =  is_dir('public://events/event_'.$event_detail->nid);
    if($bFileExists){
       global $base_url;
       $list_im = $base_url.'/sites/default/files/events/event_'.$event_detail->nid.'/1_thumb.jpg'; 
       $detail_im = $base_url.'/sites/default/files/events/event_'.$event_detail->nid.'/1_wide.jpg'; 
       
       $event_images['list_img'] = $list_im;
       $event_images['detail_img'] = $detail_im;
    
        
    }else{
    
       $event_images['list_img'] = isset($event_detail->field_list_image['und'][0]['uri']) ? file_create_url($event_detail->field_list_image['und'][0]['uri']) :'';
       $event_images['detail_img'] = isset($event_detail->field_detail_image['und'][0]['uri']) ? file_create_url($event_detail->field_detail_image['und'][0]['uri']) : '';
    }
    
    $event_list['images'] = (!empty($event_images)) ? $event_images : array();
    
    
     $all_event_list[] = $event_list;
    }
    
        $msg = '';
        $res = array('_resultflag' => 1,'_totalcount' => $total_events, 'event_list' => $all_event_list);
        return services_error($msg, 200, $res);
    
    
    
}else{
    //No data found.
    
        $msg = 'No Record Found.';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res); 
}
        
}  else {
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
    
}


function event_details($data){
    
    $security_token = constant("SECURE");
    $token = $data['token'];
    $nid = $data['id'];
    
    if($token == $security_token){
    
       
    $event_qry = db_select('node','n');
    $event_qry->fields('n',array('nid','title'));
    $event_qry->condition('n.type','event_calendar');
    $event_qry->condition('n.nid',$nid);
    $query = $event_qry->execute();

$event_list = array();

if($query->rowCount() >0){
    
    foreach ($query as $eq){
     
        $event_detail = node_load($eq->nid);
        
        $event_list['id'] = isset($event_detail->nid) ? $event_detail->nid : '';
        $event_list['name'] = isset($event_detail->title) ? $event_detail->title : '';
        $find_key = locale_language_list();
        
        $lang_list = array();
        if(!empty($event_detail->field_language_listing['und'])){
                foreach ($event_detail->field_language_listing['und'] as $l){
                    
                    $lang_list[] = $l['value'];
                }
               $language = implode(',', $lang_list);
        }else{
            $language = isset($event_detail->language) ? $find_key[$event_detail->language] : '';
        }
        
        $event_list['language'] = $language;
        
        $event_list['description'] = isset($event_detail->body['und'][0]['value']) ? $event_detail->body['und'][0]['value'] : '';
        $city = node_load($event_detail->field_event_city['und'][0]['nid']);
        $event_list['organization'] = isset($city->title) ? $city->title : '';
        
        $org = node_load($event_detail->field_event_organization['und'][0]['nid']);
        $event_list['organization'] = isset($org->title) ? $org->title : '';
        
        $event_list['category'] = isset($event_detail->field_event_category['und'][0]['value']) ? $event_detail->field_event_category['und'][0]['value'] : '';
        
        $subcat = node_load($event_detail->field_event_subcategory['und'][0]['nid']);
        $event_list['subcategory'] = isset($subcat->title) ? $subcat->title : '';
        $event_list['contact_no'] = isset($event_detail->field_contact_number['und'][0]['value']) ? $event_detail->field_contact_number['und'][0]['value'] : '';
       
        $event_list['event_entry'] = isset($event_detail->field_event_entry['und'][0]['value']) ? $event_detail->field_event_entry['und'][0]['value'] : '';
        $event_list['fee_india'] = isset($event_detail->field_fee_india['und'][0]['value']) ? $event_detail->field_fee_india['und'][0]['value'] : '';
        $event_list['fee_foreign'] = isset($event_detail->field_fee_foreign['und'][0]['value']) ? $event_detail->field_fee_foreign['und'][0]['value'] : '';
        $event_list['entry_criteria'] = isset($event_detail->field_entry_criteria['und'][0]['value']) ? $event_detail->field_entry_criteria['und'][0]['value'] : '';
       
        $event_list['venue'] = isset($event_detail->field_venue['und'][0]['value']) ? $event_detail->field_venue['und'][0]['value'] : '';
        
        $person = array();
        $persons = array();
        
    foreach ($event_detail->field_person_type['und'] as $p){
        $person['By'] = $p['field_by']['und'][0]['value'];
        $person['person_name'] = $p['field_name_of_person']['und'][0]['value'];
        $persons[] = $person;
    }
    
    $event_list['by_whom'] = (!empty($persons)) ? $persons : array();
    
   
    $event_list['lat'] = isset($event_detail->field_map_address['und'][0]['lat']) ? $event_detail->field_map_address['und'][0]['lat'] : '';
    $event_list['lng'] = isset($event_detail->field_map_address['und'][0]['lng']) ? $event_detail->field_map_address['und'][0]['lng'] : '';
    
    if($event_detail->event_calendar_date['und'][0]['value'] != '' && $event_detail->event_calendar_date['und'][0]['value2'] != ''){
        $event_list['from_date'] = isset($event_detail->event_calendar_date['und'][0]['value']) ? date('d-m-Y', strtotime($event_detail->event_calendar_date['und'][0]['value'])) : '';
        $event_list['end_date'] = isset($event_detail->event_calendar_date['und'][0]['value2']) ? date('d-m-Y', strtotime($event_detail->event_calendar_date['und'][0]['value2'])) : '';
    }  else {
    
        $event_list['from_date'] = isset($event_detail->field_custom_schedule['und'][0]['value']) ? date('d-m-Y',  strtotime($event_detail->field_custom_schedule['und'][0]['value'])): '';
        $event_list['end_date'] = '';//in custom date end date is not available,
    }
    $event_time = array();
    $e_time = array();
    
    foreach ($event_detail->field_time['und'] as $t){
        
        $st1 = strlen($t['field_event_start_time']['und'][0]['value'] > 1) ? $t['field_event_start_time']['und'][0]['value'] : '0'.$t['field_event_start_time']['und'][0]['value'];
        $st2 = strlen($t['field_event_start_minutes']['und'][0]['value'] > 1) ? $t['field_event_start_minutes']['und'][0]['value'] : '0'.$t['field_event_start_minutes']['und'][0]['value'];
        
        $end1 = strlen($t['field_event_end_time_hr']['und'][0]['value'] > 1) ? $t['field_event_end_time_hr']['und'][0]['value'] : '0'.$t['field_event_end_time_hr']['und'][0]['value'];
        $end2 = strlen($t['field_enent_end_time_minuetes']['und'][0]['value'] > 1) ? $t['field_enent_end_time_minuetes']['und'][0]['value'] : '0'.$t['field_enent_end_time_minuetes']['und'][0]['value'];
        
        $min1 = strlen($st2) > 1 ? $st2 : '0'.$st2;
        $min2 = strlen($end2) > 1 ? $end2 : '0'.$end2;
        
        $min0 = strlen($st1) > 1 ? $st1 : '0'.$st1;
        $end0 = strlen($end1) > 1 ? $end1 : '0'.$end1;
        
        $e_time['Event_start_time'] = $min0.':'.$min1;
        $e_time['Event_end_time'] = $end0.':'.$min2;
        
        
        //$e_time['Event_start_time'] = $t['field_event_start_time']['und'][0]['value'].':'.$t['field_event_start_minutes']['und'][0]['value'];
        //$e_time['Event_end_time'] = $t['field_event_end_time_hr']['und'][0]['value'].':'.$t['field_enent_end_time_minuetes']['und'][0]['value'];
        $event_time[] = $e_time;
    }
    $event_list['event_time'] = (!empty($event_time)) ? $event_time : array();
    
    
      //images
    
    $event_images = array();
    $bFileExists =  is_dir('public://events/event_'.$event_detail->nid);
    if($bFileExists){
       global $base_url;
       $list_im = $base_url.'/sites/default/files/events/event_'.$event_detail->nid.'/1_thumb.jpg'; 
       $detail_im = $base_url.'/sites/default/files/events/event_'.$event_detail->nid.'/1_wide.jpg'; 
       
       $event_images['list_img'] = $list_im;
       $event_images['detail_img'] = $detail_im;
    
        
    }else{
    
       $event_images['list_img'] = isset($event_detail->field_list_image['und'][0]['uri']) ? file_create_url($event_detail->field_list_image['und'][0]['uri']) :'';
       $event_images['detail_img'] = isset($event_detail->field_detail_image['und'][0]['uri']) ? file_create_url($event_detail->field_detail_image['und'][0]['uri']) : '';
    }
    
    $event_list['images'] = (!empty($event_images)) ? $event_images : array();
    
    }
    
     $all_event_list[] = $event_list;
     
        $msg = '';
        $res = array('_resultflag' => 1,'event_detail' => $all_event_list);
        return services_error($msg, 200, $res);
}else{
    
        $msg = 'No Record Found.';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res); 
    
}
    
    }  else {
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
    
}


function post_comments($data){
    
    $security_token = constant("SECURE");
    $token = $data['token'];
    
    $comment = $data['comment'];
    $event_id = $data['event_id'];
    $name = $data['name'];
    $mobile = $data['mobile'];
    $rating = $data['rating'];
    $device_id = $data['device_id'];
    
     if($token == $security_token){
       
         $newNode = (object) NULL;
                        $newNode->type = 'feedback';
                        $newNode->title = 'test_title_'.time();
                        $newNode->uid = 1;
                        $newNode->language = 'en';                      
                        $newNode->created = strtotime("now");
                        $newNode->changed = strtotime("now");
                        $newNode->status = 0;
                        $newNode->comment = 0;
                        $newNode->promote = 0;
                        $newNode->moderate = 0;
                        $newNode->sticky = 0;
                        // add CCK field data
                        $newNode->body['und'][0]['value'] = isset($comment) ? $comment : '';
                        $newNode->field_event['und'][0]['nid'] = isset($event_id) ? $event_id : '';
                        $newNode->field_name['und'][0]['value'] = isset($name) ? $name : '';
                        $newNode->field_mobile['und'][0]['value'] = isset($mobile) ? $mobile : '';
                        $newNode->field_rating['und'][0]['value'] = isset($rating) ? $rating : '';
                        $newNode->field_device_id['und'][0]['value'] = isset($device_id) ? $device_id : '';
                        
                        node_save($newNode);
        if($newNode->nid != ''){
            
        $msg = '';
        $res = array('_resultflag' => 1,'message' => 'Post Comment Successfully');
        return services_error($msg, 200, $res);
        
            
        }else{
            
        $msg = '';
        $res = array('_resultflag' => 0,'message' => 'Post Comment Unsuccessfully');
        return services_error($msg, 406, $res);
            
        }                
         
         
         
     }else {
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
    
}

function comment_lists($data){
    
    $security_token = constant("SECURE");
    $token = $data['token'];
    $event_id = $data['event_id'];
    
    //$index = $data['index'];
    $total_record = $data['totalrecord'];
    
    $add = 0;
    $index = ($data['index'] > 0) ? $data['index'].''.$add :  $data['index'];
    
    
      if($token == $security_token){
        
       //get total count
          
        $cmt_qry = db_select('node','n');
        $cmt_qry->fields('n',array('nid','title'));
        $cmt_qry->innerJoin('field_data_field_event','e','e.entity_id = n.nid');
        $cmt_qry->condition('e.field_event_nid',$event_id);
        $cmt_qry->condition('n.status',1);
        
        $query_total_count = $cmt_qry->execute();   
        $total_comment = $query_total_count->rowCount();
        
        //end of the code  
          
        $cmt_qry = db_select('node','n');
        $cmt_qry->fields('n',array('nid','title'));
        $cmt_qry->innerJoin('field_data_field_event','e','e.entity_id = n.nid');
        $cmt_qry->condition('e.field_event_nid',$event_id);
        $cmt_qry->condition('n.status',1);
        
        if($index != '' && $total_record != ''){
            $cmt_qry->range($index, $total_record);
        }
        
        $query = $cmt_qry->execute();
        
       $comment_list = array();
       
       if($query->rowCount() > 0){
           
           foreach ($query as $qr){
               
          $comment_detail = node_load($qr->nid);
        
          $comment_list['id'] = isset($comment_detail->nid) ? $comment_detail->nid : '';
          $comment_list['comment'] = isset($comment_detail->body['und'][0]['value']) ? $comment_detail->body['und'][0]['value'] : '';
          $comment_list['event_id'] = isset($comment_detail->field_event['und'][0]['nid']) ? $comment_detail->field_event['und'][0]['nid'] : '';
          $comment_list['name'] = isset($comment_detail->field_name['und'][0]['value']) ? $comment_detail->field_name['und'][0]['value'] : '';
          $comment_list['mobile'] = isset($comment_detail->field_mobile['und'][0]['value']) ? $comment_detail->field_mobile['und'][0]['value'] : '';
          $comment_list['rating'] = isset($comment_detail->field_rating['und'][0]['value']) ? $comment_detail->field_rating['und'][0]['value'] : '';
          
          $comments[] = $comment_list;
           }
           
           
        $msg = '';
        $res = array('_resultflag' => 1, 'total_comment' =>$total_comment, 'commentlist' => $comments);
        return services_error($msg, 200, $res);  
           
           
       }else{
           
        $msg = 'No Record Found.';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);  
           
           
       } 
        
          
          
      }else {
        
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
        
    }
    
}

function add_to_fav($data){
    
     $security_token = constant("SECURE");
     
     $token = $data['token'];
     $event_id = $data['event_id'];
     $device_id = $data['device_id'];
     
     
     
     if($token == $security_token){
         
         //sif($event_id != '' && $device_id != ''){
             
             
          $chk_qry = db_select('custom_addto_fav','cf')
                       ->fields('cf', array('fid'))
                       ->condition('cf.device_id', $device_id)
                       ->condition('cf.event_nid', $event_id)
                       ->execute();
          
        if($chk_qry->rowCount() >0){
           
        $msg = '';
        $res = array('_resultflag' => 0,'message' => 'This Event already added in your favorite');
        return services_error($msg, 406, $res);
              
              
          }else{
                        
                $qry = db_insert('custom_addto_fav')
                         ->fields(array(
                             'event_nid' => $event_id,
                             'device_id' => $device_id,
                             'created' => REQUEST_TIME
                         ))
                        ->execute();
            
          }
            
           
        if($qry != ''){
            
        $msg = '';
        $res = array('_resultflag' => 1,'message' => 'Event successfully added to favorite');
        return services_error($msg, 200, $res); 
                
        }else{
        
            $msg = '';
            $res = array('_resultflag' => 0,'message' => 'Unable to add as a favorite');
            return services_error($msg, 406, $res); 
        } 
             
        //}
         
         
     }  else {
         
         
        $msg = 'You are not Authorized to access The Application';
        $res = array('_resultflag' => 0,'message' => $msg);
        return services_error($msg, 406, $res);
     
         
     }
    
}



?>