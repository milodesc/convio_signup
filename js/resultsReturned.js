(function($, Drupal) {
  Drupal.ajax.prototype.commands.fadeAwayStatusMessage = function(ajax, response, status) {
    window.setTimeout(function() {
      $("#" + response.targetElement).children().fadeOut();
    }, 2000);
  };
}(jQuery, Drupal));