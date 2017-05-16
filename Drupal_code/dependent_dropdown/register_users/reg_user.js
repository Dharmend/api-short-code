/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


jQuery(function($) {
    
    $(document).ready(function() {
        
       var path_name = $(location).attr('pathname');
       var res = path_name.split("/");
       var last = res[res.length - 1];
       //alert(last);
       if(last == 'manage-events'){
            
            var default_org = getParameterByName('field_event_organization_nid');
            if(default_org.length == '0')
             {
             
                var $el = $("#edit-field-event-organization-nid");
                $el.html(' ');
             
                $("#edit-field-event-organization-nid").append('<option value="All">All</option>');
                
                
              }else{
                  search_manage_event_city_loading();
                  $("#edit-field-event-organization-nid").val(default_org);
              }
              
             var default_city = getParameterByName('field_event_subcategory_nid');
             if(default_city.length == '0')
             {
                var $el = $("#edit-field-event-subcategory-nid");
                $el.html(' ');
                $("#edit-field-event-subcategory-nid").append('<option value="All">All</option>');
              
              }else{
		 	  
                  search_manage_event_subcat();
                  $("#edit-field-event-subcategory-nid").val(default_city);
              }
              
    }
    
    //feedback listing ajax
    if(last == 'feedback-listing'){
            
             var feed_city = getParameterByName('field_event_subcategory_nid');
             if(feed_city.length == '0')
             {
                var $feed_el = $("#edit-field-event-subcategory-nid");
                $feed_el.html(' ');
                $("#edit-field-event-subcategory-nid").append('<option value="All">All</option>');
              }else{
                  search_manage_event_subcat();
                  $("#edit-field-event-subcategory-nid").val(feed_city);
              }
              
    }
       var n = res[res.length - 3];
       if(last == 'edit' && n == 'node'){
            create_event_city_org_load();
            cat_subcat_ajax_fetching_load();
            //alert('Test file');
            //var $el_data = $("#edit-field-event-organization-und");
           // $el_data.val('220');
       }
       if(last == 'edit' && n == 'user'){
           
           create_user_city_org_load();
           
       }
       var add_event = res[res.length - 2];
       if(last = 'event-calendar' && add_event == 'add'){
           
           $('table#field-time-values tr.even:eq(0)').remove();
           
           var $org_val = $("#edit-field-event-organization-und");
               $org_val.html(' ');
               $("#edit-field-event-organization-und").append('<option value="_none"> - None - </option>');
               
            var $subcat_vel = $("#edit-field-event-subcategory-und");
               $subcat_vel.html(' ');
               $("#edit-field-event-subcategory-und").append('<option value="_none"> - None - </option>');
           
       }
       
       if(last = 'create' && add_event == 'people'){
           
           var $user_org = $("#edit-field-organization-und");
               $user_org.html(' ');
            $("#edit-field-organization-und").append('<option value="_none"> - None - </option>');   
            
       }
       
  
});

function getParameterByName(name) {
    name = name.replace(/[\[]/, "\\[").replace(/[\]]/, "\\]");
    var regex = new RegExp("[\\?&]" + name + "=([^&#]*)"),
        results = regex.exec(location.search);
    return results == null ? "" : decodeURIComponent(results[1].replace(/\+/g, " "));
}

 
  $("#edit-field-city-und").change(function() {
     
      create_user_city_org();
     
  });
  
  function create_user_city_org(){
      
       var city = $("#edit-field-city-und").val();
      
      $.ajax({
        type:'GET',
        //url: 'http://localhost/drupal/moceventapp/trunk/user/org_list',
        url: Drupal.settings.basePath + 'user/org_list/'+ city,
        data: '',
        beforeSend: function(){
                    $('.loader').show();
        },
        success : function(data, textStatus, xhr){
            $('.loader').hide();
            
            var $el = $("#edit-field-organization-und");
            $el.html(' ');
            
            //$('#edit-field-organization-und:gt(0)').remove();
            
            $.each(data, function(key, value) {
                //alert('key is'+key+'Value are'+value);
                $('#edit-field-organization-und').prepend(
                '<option value="' + key + '">' + value + '</option>'
                );
                
                console.log(this);
                
          });
            //Arrange elements of an array
                
                var selectList = $('#edit-field-organization-und option');

                    $("#edit-field-organization-und").html($("#edit-field-organization-und option").sort(function (a, b) {
				return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
               }))
          
          
          $el.val('_none');
       },
        error : function(xhr, textStatus, errorThrown){
            
           // alert('Error Please try again');
            
        }
      });
}


  function create_user_city_org_load(){
      
       var city = $("#edit-field-city-und").val();
      
      $.ajax({
        type:'GET',
        //url: 'http://localhost/drupal/moceventapp/trunk/user/org_list',
        url: Drupal.settings.basePath + 'user/org_list/'+ city,
        data: '',
        beforeSend: function(){
                    $('.loader').show();
        },
        success : function(data, textStatus, xhr){
            $('.loader').hide();
            
            var $el = $("#edit-field-organization-und");
            $el.html(' ');
            
            //$('#edit-field-organization-und:gt(0)').remove();
            
            $.each(data, function(key, value) {
                //alert('key is'+key+'Value are'+value);
                $('#edit-field-organization-und').prepend(
                '<option value="' + key + '">' + value + '</option>'
                );
                
                console.log(this);
                
          });
            //Arrange elements of an array
                
                var selectList = $('#edit-field-organization-und option');

                    $("#edit-field-organization-und").html($("#edit-field-organization-und option").sort(function (a, b) {
				return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
               }))
          
          //$el.val('_none');
          //Add Default value

               var path_name = $(location).attr('pathname');
               var res = path_name.split("/");
               var user_id = res[res.length - 2];
              
            $.ajax({
                   type:'GET',
                   url:Drupal.settings.basePath + 'user/load/'+user_id,
                   data:'',
                   success : function(data, textStatus, xhr){
                                              
                       $.each(data, function(key, value) {
                           if(key == 'org'){
                               $('#edit-field-organization-und').val(value);
                           }
                           
                        });
                   },
                   
               }); 
          
          
          
       },
        error : function(xhr, textStatus, errorThrown){
            
           // alert('Error Please try again');
            
        }
      });
}


  
 // Make city and organization dependent based on logedin user,
 
        $("#edit-field-event-city-und").change(function() {
            
            create_event_city_org();
//            var def_v = $("#edit-field-event-organization-und");
//            def_v.val('_none');

     });
     
    function create_event_city_org(){
         
                var event_city = $("#edit-field-event-city-und").val();

                $.ajax({
                type:'GET',
                url: Drupal.settings.basePath + 'event/org_list/'+ event_city,
                data: '',
                beforeSend: function(){
                    $('.loader').show();
                },
                success : function(data, textStatus, xhr){
                    $('.loader').hide();
                    var $el = $("#edit-field-event-organization-und");
                    $el.html(' ');

                    //$('#edit-field-organization-und:gt(0)').remove();

                    $.each(data, function(key, value) {
                        //alert('key is'+key+'Value are'+value);
                        $('#edit-field-event-organization-und').prepend(
                        '<option value="' + key + '">' + value + '</option>'
                        );

                        console.log(this);

                  });
                  
                 //Arrange elements of an array
                var selectList = $('#edit-field-event-organization-und option');

                    $("#edit-field-event-organization-und").html($("#edit-field-event-organization-und option").sort(function (a, b) {
				return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
               }))
                  
                  
                  $el.val('_none');
                  //
                  
                  
            },
                error : function(xhr, textStatus, errorThrown){

                    //alert('Error'+xhr+'status'+textStatus+'thro'+errorThrown);

                }
              }); 
     }
     
    function create_event_city_org_load(){
         
                var event_city = $("#edit-field-event-city-und").val();

                $.ajax({
                type:'GET',
                url: Drupal.settings.basePath + 'event/org_list/'+ event_city,
                data: '',
                //async:false,
                beforeSend: function(){
                    $('.loader').show();
                },
                success : function(data, textStatus, xhr){
                    
                    $('.loader').hide();
                    var $el = $("#edit-field-event-organization-und");
                    $el.html(' ');

                    //$('#edit-field-organization-und:gt(0)').remove();

                    $.each(data, function(key, value) {
                       $('#edit-field-event-organization-und').prepend(
                        '<option value="' + key + '">' + value + '</option>'
                        );

                        console.log(this);

                  });
                //$el.val('220');
                //Arrange elements of an array
                
                var selectList = $('#edit-field-event-organization-und option');

                    $("#edit-field-event-organization-und").html($("#edit-field-event-organization-und option").sort(function (a, b) {
				return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
               }))
               
               //Add another responce 
               var path_name = $(location).attr('pathname');
               var res = path_name.split("/");
               var edit_event_id = res[res.length - 2];
               
               $.ajax({
                   
                   type:'GET',
                   url:Drupal.settings.basePath + 'event/edit/'+edit_event_id,
                   data:'',
                   success : function(data, textStatus, xhr){
                       //alert('my data'+data+'');
                       
                       $.each(data, function(key, value) {
                           //alert('key'+key+'value'+value);
                           
                           if(key == 'subcat'){
                               $('#edit-field-event-subcategory-und').val(value);
                           }else if(key == 'org'){
                               $('#edit-field-event-organization-und').val(value);
                           }
                           
                        });
                   },
                   
               });
               
               
               
               
               
                  
            },
                error : function(xhr, textStatus, errorThrown){

                    alert('Error'+xhr+'status'+textStatus+'thro'+errorThrown);

                }
              }); 
     }
     
     
     
     //manage event city dropdown
     $("#edit-field-event-city-nid").change(function(){
         search_manage_event_city_loading();
     });
     
     function search_manage_event_city_loading(){
         
                var mange_event_city = $("#edit-field-event-city-nid").val();
                $.ajax({
                type:'GET',
                url: Drupal.settings.basePath + 'manage_event/org_list/'+ mange_event_city,
                data: '',
                beforeSend: function(){
                    $('.loader').show();
                },
                success : function(data, textStatus, xhr){
                    $('.loader').hide();
                    var $el = $("#edit-field-event-organization-nid");
                    $el.html(' ');
                    
                   $.each(data, function(key, value) {
                        $('#edit-field-event-organization-nid').prepend(
                        '<option value="' + key + '">' + value + '</option>'
                        );

                        console.log(this);

                  });
                //Arrange elements of an array
                
                var selectList = $('#edit-field-event-organization-nid option');

                    $("#edit-field-event-organization-nid").html($("#edit-field-event-organization-nid option").sort(function (a, b) {
				return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
               }))
                
                
                  
            var default_org1 = getParameterByName('field_event_organization_nid');
            if(default_org1.length == '0')
             {
//                var $el = $("#edit-field-event-organization-nid");
//                $el.html(' ');
                $("#edit-field-event-organization-nid").val('All');
              }else{
                  
                  $("#edit-field-event-organization-nid").val(default_org1);
              }   
                  
                  
                  
               },
                error : function(xhr, textStatus, errorThrown){
               }
              });
         
     }
     
     //Manage event sub-cat listing
     $("#edit-field-event-category-value").change(function(){
         
         search_manage_event_subcat();

     });
     
     function search_manage_event_subcat(){
         
         
           var mange_event_cat = $("#edit-field-event-category-value").val();

                $.ajax({
                type:'GET',
                url: Drupal.settings.basePath + 'manage_event/subcat_list/'+ mange_event_cat,
                data: '',
                beforeSend: function(){
                    $('.loader').show();
                },
                success : function(data, textStatus, xhr){
                    $('.loader').hide();
                    var $el = $("#edit-field-event-subcategory-nid");
                    $el.html(' ');
                    
                   $.each(data, function(key, value) {
                        $('#edit-field-event-subcategory-nid').prepend(
                        '<option value="' + key + '">' + value + '</option>'
                        );

                        console.log(this);

                  });
              //arrage elements of 
              
              var selectList = $('#edit-field-event-subcategory-nid option');

                    $("#edit-field-event-subcategory-nid").html($("#edit-field-event-subcategory-nid option").sort(function (a, b) {
				if(a.text == 'All'){
                                    return -100;
                                }else{
                                    return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
                                }
                                    
               }))
              
              //End of the code
                    
            var default_org2 = getParameterByName('field_event_subcategory_nid');
            if(default_org2.length == '0')
             {
                $("#edit-field-event-subcategory-nid").val('All');
             }else{
                  
                  $("#edit-field-event-subcategory-nid").val(default_org2);
              }
                    
                    
                    
                    
                    
               },
                error : function(xhr, textStatus, errorThrown){
               }
              });
         
         
     }
     
    //create event cat subcat dropdown 
    $("#edit-field-event-category-und").change(function(){
        
         cat_subcat_ajax_fetching();
      
         
     });
     
     
     function cat_subcat_ajax_fetching(){
         
         
            var mange_event_cat = $("#edit-field-event-category-und").val();

                $.ajax({
                type:'GET',
                url: Drupal.settings.basePath + 'add_event/subcat_list/'+ mange_event_cat,
                data: '',
                beforeSend: function(){
                    $('.loader').show();
                },
                success : function(data, textStatus, xhr){
                    $('.loader').hide();
                    var $el = $("#edit-field-event-subcategory-und");
                    $el.html(' ');
                    
                   $.each(data, function(key, value) {
                        $('#edit-field-event-subcategory-und').prepend(
                        '<option value="' + key + '">' + value + '</option>'
                        );

                        console.log(this);

                  });
                  
                  //Arrange elements of an array
                var selectList = $('#edit-field-event-subcategory-und option');

                    $("#edit-field-event-subcategory-und").html($("#edit-field-event-subcategory-und option").sort(function (a, b) {
				if(a.text == 'All'){
                                    return -100;
                                }else{
                                    return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
                                }
               }))
                  
                   $el.val('_none');
               },
                error : function(xhr, textStatus, errorThrown){
               }
              });
     }
     
     
     
     function cat_subcat_ajax_fetching_load(){
            
           
        var mange_event_cat = $("#edit-field-event-category-und").val();

                $.ajax({
                type:'GET',
                url: Drupal.settings.basePath + 'add_event/subcat_list/'+ mange_event_cat,
                data: '',
                beforeSend: function(){
                    $('.loader').show();
                },
                success : function(data, textStatus, xhr){
                    $('.loader').hide();
                    var $el = $("#edit-field-event-subcategory-und");
                    $el.html(' ');
                  
                   $.each(data, function(key, value) {
                        $('#edit-field-event-subcategory-und').prepend(
                        '<option value="' + key + '">' + value + '</option>'
                        );

                        console.log(this);

                  });
                  
                  //Arrange elements of an array
                var selectList = $('#edit-field-event-subcategory-und option');

                    $("#edit-field-event-subcategory-und").html($("#edit-field-event-subcategory-und option").sort(function (a, b) {
				if(a.text == 'All'){
                                    return -100;
                                }else{
                                    return a.text == b.text ? 0 : a.text < b.text ? -1 : 1
                                }
               }))
                  
                  //$el.val('_none');
               },
                error : function(xhr, textStatus, errorThrown){
               }
              });
            
            
     }
 
 
  
  
  
  
});
