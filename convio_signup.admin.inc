<?php

/**
 * @file
 * Admin page callbacks for the convio_signup module.
 */

/**
 * Prepares a table with the details and actions of all Convio Signup forms.
 */
function convio_signup_admin() {

  $results = db_query("SELECT form_id, title, description FROM {convio_signup_form_blocks}");

  foreach ($results as $row) {
    $actions = array(
      'configure' => l(t('Configure'), sprintf('admin/structure/block/manage/convio_signup/%d/configure', $row->form_id)),
      'delete'    => l(t('Delete'), sprintf('admin/structure/convio_signup/%d/delete', $row->form_id)),
    );

    $rows[] = array(
      'id'   => $row->form_id,
      'title' => $row->title,
      'description' => $row->description,
      'ops'  => implode(' | ', $actions),
    );
  }

  $main_content = "<h2>There are no blocks set up.</h2>";
  if (!empty($rows)) {
    $header = array(
      'id'   => t('Block ID'),
      'title' => t('title'),
      'desc' => t('Description'),
      'ops'  => t('Operations'),
    );
    $main_content = theme('table', array('header' => $header, 'rows' => $rows));
  }

  $create_form_button = l(t('Create a Convio Signup Form block'), 'admin/structure/convio_signup/add', array('attributes' => array('class' => array('button'))));
  $convio_api_config_button = l(t('Configure the connection to Convio'), 'admin/config/system/convio_api_config', array('attributes' => array('class' => array('button'))));

  return $main_content . $create_form_button . $convio_api_config_button;
}

/**
 * Form constructor for creating a new Convio Signup form block.
 *
 * @see convio_signup_add_validate()
 * @see convio_signup_add_submit()
 *
 * @ingroup forms
 */
function convio_signup_add($form, &$form_state) {

  $form['overview'] = array(
    '#markup' => t('Create a new Convio Signup Form block by filling out and submitting the form below.'),
  );

  $form['external_facing_fields'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form display configuration'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => 'Fields to configure the display of the Convio Signup Form',
  );

  $form['external_facing_fields']['title'] = array(
    '#title' => t('Form Title'),
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 512,
  );

  $form['external_facing_fields']['email_field_placeholder'] = array(
    '#title' => t('Email Field Placeholder'),
    '#description' => t("The text that displays inside the email field before the user enters their email address."),
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 512,
  );

  $form['external_facing_fields']['helper_text'] = array(
    '#title' => t('User Helper Text'),
    '#description' => t('Text that instucts the user how to use the form.'),
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 255,
  );

  $form['external_facing_fields']['submission_success_msg'] = array(
    '#title' => t('Success Message'),
    '#description' => t('Text that appears after the user successfully submits their email address. Defaults to "Thanks! We\'ll be in touch soon!"'),
    '#type' => 'textfield',
    '#attributes' => array(
      'placeholder' => "Thanks! We'll be in touch soon!",
    ),
    '#size' => 30,
    '#maxlength' => 255,
  );

  $form['external_facing_fields']['submit_button_text'] = array(
    '#title' => t("Submit Button Text"),
    '#description' => t("What should the button the user clicks to submit their email address say? Defaults to 'Submit'."),
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 255,
    '#attributes' => array(
      'placeholder' => 'Submit',
    ),
  );

  $form['description'] = array(
    '#title' => t('A brief description of the Convio Signup Form block'),
    '#type' => 'textfield',
    '#size' => 120,
    '#maxlength' => 1024,
    '#required' => TRUE,
  );

  $form['source'] = array(
    '#title' => t('Source:'),
    '#description' => t('Text to associate with newly created constituent records to identify how or from where the record was added.'),
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 255,
  );

  $form['sub_source'] = array(
    '#title' => t('Subsource:'),
    '#description' => t('Further detail to save with the "source" information.'),
    '#type' => 'textfield',
    '#size' => 30,
    '#maxlength' => 255,
  );

  $form['no_welcome'] = array(
    '#title' => t('Send welcome email to new constituents created by this form?:'),
    '#description' => t('Select \'Yes\' to send a welcome email (configured in Convio Luminate Online) to new constituents.'),
    '#type' => 'radios',
    '#options' => array(
      'f' => 'Yes',
      't' => 'No',
    ),
    '#default_value' => 't',
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/structure/convio_signup'),
  );

  return $form;
}

/**
 * Form submission handler for convio_signup_add().
 *
 * @see convio_signup_add_validate()
 */
function convio_signup_add_submit($form, &$form_state) {
  $values = $form_state['values'];

  $data = array(
    'title' => ($values['title']) ? ($values['title']) : NULL,
    'description' => ($values['description']) ? ($values['description']) : NULL,
    'email_field_placeholder' => ($values['email_field_placeholder']) ? ($values['email_field_placeholder']) : NULL,
    'helper_text' => ($values['helper_text']) ? ($values['helper_text']) : NULL,
    'submission_success_msg' => ($values['submission_success_msg']) ? $values['submission_success_msg'] : NULL,
    'source' => ($values['source']) ? $values['source'] : NULL,
    'sub_source' => ($values['sub_source']) ? $values['sub_source'] : NULL,
    'submit_button_text' => ($values['submit_button_text']) ? $values['submit_button_text'] : NULL,
    'no_welcome' => ($values['no_welcome']) ? $values['no_welcome'] : 't',
  );

  $result = drupal_write_record('convio_signup_form_blocks', $data);

  if ($result) {
    drupal_set_message('Your signup form has been created');
  }
  else {
    drupal_set_message('There was an error creating your signup form', 'error');
  }

  drupal_goto('admin/structure/convio_signup');
}

/**
 * Form constructor for deleting a Convio Signup form block.
 *
 * @see convio_signup_delete_validate()
 * @see convio_signup_delete_submit()
 *
 * @ingroup forms
 */
function convio_signup_delete($form, &$form_state, $form_id) {
  $result = db_query("SELECT title, description FROM {convio_signup_form_blocks} where form_id = :form_id", array(':form_id' => $form_id))->fetchObject();
  $form['warning'] = array('#markup' => '<h2>You are about to delete the following Convio Signup Form: "' . $result->description . '." This cannot be undone!</h2>');

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/structure/convio_signup'),
  );
  return $form;
}

/**
 * Form submission handler for convio_signup_delete().
 *
 * @see convio_signup_validate()
 */
function convio_signup_delete_submit($form, &$form_state) {
  $form_id = $form_state['build_info']['args'][0];
  convio_signup_remove($form_id);
  drupal_goto('admin/structure/convio_signup');
}

/**
 * Remove the Convio Signup Block form from the database.
 *
 * @param int $form_id
 *   The ID of the form being deleted.
 */
function convio_signup_remove($form_id) {
  $res = db_query('DELETE from {convio_signup_form_blocks} WHERE form_id = :form_id', array(':form_id' => $form_id));
  if ($res) {
    drupal_set_message('The Convio signup form has been deleted.');
  }
  else {
    drupal_set_message('There was an error deleting the signup form.', 'error');
  }
  $res = db_query("DELETE from {block} WHERE module = 'convio_signup_form_blocks' AND delta = :form_id", array(':form_id' => $form_id));
  if (!$res) {
    drupal_set_message('There was an error deleting the form from the blocks table.', 'error');
  }
}
