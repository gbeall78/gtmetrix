<?php

/**
 * @file
 * GTmetrix module configuration form.
 */

/**
 * Page callback: GTmetrix settings.
 * @see gtmetrix_menu()
 * @todo Retrieve options for $form['gtmetrix_settings']['location'] via the
 * GTmetrix API.
 */
function gtmetrix_form($form, &$form_state) {
  $form['gtmetrix_login'] = array(
    '#type' => 'fieldset',
    '#title' => t('GTmetrix login details'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['gtmetrix_login']['login'] = array(
    '#type' => 'textfield',
    '#title' => t('Login email'),
    '#default_value' => _get_gtmetrix_setting('login'),
    '#description' => t('Enter the email address to login to GTmetrix.'),
    '#required' => TRUE,
    '#element_validate' => array('_element_email_validate'),
  );
  $form['gtmetrix_login']['apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#default_value' => _get_gtmetrix_setting('apikey'),
    '#description' => t('Enter the API Key to login to GTmetrix.'),
    '#required' => TRUE,
    '#element_validate' => array('_element_alnum_validate'),
  );
  $form['gtmetrix_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('GTmetrix settings'),
    '#weight' => 0,
  );
  $form['gtmetrix_settings']['location'] = array(
    '#type' => 'select',
    '#title' => 'Test locations',
    '#description' => t('Select the location testing will be performed from.'),
    '#options' => array(
      0 => t('Vancouver, Canada'),
      1 => t('London, UK'),
      2 => t('Sydney, Australia'),
      3 => t('Dallas, USA'),
      4 => t('Mumbai, India'),
      5 => t('Sao Paulo, Brazil'),
    ),
    '#default_value' => _get_gtmetrix_setting('location'),
  );
  $form['gtmetrix_settings']['adblock'] = array(
    '#type' => 'checkbox',
    '#title' => 'Enable Adblock',
    '#description' => t('Selecting this will prevent ads loading using Adblock Plus.'),
    '#default_value' => _get_gtmetrix_setting('adblock'),
  );
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form;
}

/**
 * Checks whether the given element is a valid email address.
 *
 * @param array $element
 *   A structured array containing the elements and properties of the form.
 * @param array $form_state
 *   An array that contains information about the form's current state during
 *  processing
 */
function _element_email_validate($element, &$form_state) {
  if (!valid_email_address($element['#value'])) {
    form_error($element, t('The @name option must contain a valid email address.', array('@name' => $element['#title'])));
  }
}

/**
 * Checks whether the given element is alphanumeric only.
 *
 * @param array $element
 *   A structured array containing the elements and properties of the form.
 * @param array $form_state
 *   An array that contains information about the form's current state during
 *  processing
 */
function _element_alnum_validate($element, &$form_state) {
  if (!ctype_alnum($element['#value'])) {
    form_error($element, t('The @name option must contain letters and numbers only.', array('@name' => $element['#title'])));
  }
}

/**
 * Implements hook_submit().
 */
function gtmetrix_form_submit($form, &$form_state) {
  $query = db_merge('gtmetrix_settings')
    ->key(array('id' => 1))
    ->insertFields(array(
      'login' => $form_state['values']['login'],
      'apikey' => $form_state['values']['apikey'],
      'location' => $form_state['values']['location'],
      'adblock' => $form_state['values']['adblock'],
    ))
    ->updateFields(array(
      'login' => $form_state['values']['login'],
      'apikey' => $form_state['values']['apikey'],
      'location' => $form_state['values']['location'],
      'adblock' => $form_state['values']['adblock'],
    ))
    ->execute();
  drupal_set_message(t('The configuration has been updated.'));
}

/**
 * Retrieve a variable from the database.
 *
 * @param string $field
 *   Field to retrieve the variable from.
 */
function _get_gtmetrix_setting($field) {
  $query = db_select('gtmetrix_settings', 'g')
    ->fields('g', array($field))
    ->execute();
  return $query->fetchField(0);
}
