<?php
/**
 * @file
 * Gtmetrix module configuration form
 */

/**
 * Page callback: Gtmetrix settings
 * @see: gtmetrix_menu()
 */

function gtmetrix_form($form, &$form_state) {
  $form['gtmetrix_setting1'] = array(
    '#type' => 'textfield',
    '#title' => t('gtmetrix Setting 1'),
    '#default_value' => variable_get('gtmetrix_setting1', 2),
    '#size' => 2,
    '#description' => t('Setting decription'),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

/**
 * Implements validation from the Form API
 *
 * @param form
 *  A structured array containing the elements and properties of the form.
 * @param $form_state
 *  An array that contains information about the form's current state during
 *  processing
 */

function gtmetrix_form_validate($form, &$form_state) {
  $value_check = $form_state['values']['gtmetrix_setting1'];
  if ($value_check <= 0) {
    form_set_error('gtmetrix_setting1', t('Value must be greater than zero'));
  }
}
