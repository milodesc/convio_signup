<?php
/**
 * @file
 * Cross-file functionality
 */

function remove_file_references($file_form_name) {
  $fid = variable_get($file_form_name);
  if (!empty($fid)) {
    $file = file_load($fid);
    if (!empty($file)) {
      file_usage_delete($file, 'convio_signup');
      file_delete($file);
      variable_del($file_form_name);
    }
  }
}
