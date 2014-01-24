(function($, Drupal) {
    Drupal.ajax.prototype.commands.fadeAwayStatusMessage = function(ajax, response, status) {
        window.setTimeout(function() {
            $("#convio_signup_ajax_wrapper").children().fadeOut();
          }, 2000);
    };
}(jQuery, Drupal));