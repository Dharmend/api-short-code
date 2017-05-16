(function($) {
	$.fn.error_function = function(data) {
		//alert('dsfsdfdsfsd');
		//$('[name=data]').addclass('error');
		//$("#edit-reg-id").addClass('error');
                //$('input[name=reg_id]').addClass('error');
		$.each(data, function (index, value) {
		  //console.log(value);
		  //alert(index);
		  $('input[name='+index+']').addClass('error');
                  $('textarea[name='+index+']').addClass('error');
		  // $("#edit-reg-id").addclass('error');
		 //$('input[name=index]').addClass('error');	
		  // Will stop running after "three"
		  //return (value !== 'three');
			
		});

	};
})(jQuery);
