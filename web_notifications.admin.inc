<?php

/**
* Form callback: Web Notifications Configuration
*
* @see web_notifications_menu()
*/
function web_notifications_settings_form($form, &$form_state) {
  $form['web_notifications_public_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Push Notification Public Key'),
    '#default_value' => variable_get('web_notifications_public_key', ''),
    '#size' => 90,
    '#maxlength' => 90,
    '#description' => t('Push Notification Public Key (max. 90 characters)'),
    '#required' => TRUE,
  );

  $form['web_notifications_private_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Push Notification Private Key'),
    '#default_value' => variable_get('web_notifications_private_key', ''),
    '#size' => 50,
    '#maxlength' => 50,
    '#description' => t('Push Notification Private Key (max. 50 characters)'),
    '#required' => TRUE,
  );

  $form['web_notifications_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Push Notification Subject'),
    '#default_value' => variable_get('web_notifications_subject', ''),
    '#size' => 50,
    '#maxlength' => 50,
    '#description' => t('Contact URI for the application server as either a "mailto:" or an "https:" address'),
    '#required' => TRUE,
  );

  $form['web_notifications_query_selector'] = array(
    '#type' => 'textfield',
    '#title' => t('Button Selector'),
    '#default_value' => variable_get('web_notifications_query_selector', ''),
    '#size' => 50,
    '#maxlength' => 50,
    '#description' => t('Button ID used for subscription (without #)'),
    '#required' => TRUE,
  );
  $form['web_notifications_base_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Base URL'),
    '#default_value' => variable_get('web_notifications_base_url', 'web_notifications'),
    '#size' => 50,
    '#maxlength' => 50,
    '#description' => t('URL Used to send subscriptions'),
    '#required' => TRUE,
  );


  return system_settings_form($form);
}


/**
* Form callback: Web Notifications sending form
*
* @see web_notifications_menu()
*/
function web_notifications_sending_form($form, &$form_state) {
  $form['web_notifications_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => variable_get('web_notifications_title', ''),
    '#size' => 90,
    '#maxlength' => 90,
    '#description' => t('Push Notification Title'),
    '#required' => TRUE,
  );

  $form['web_notifications_url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => variable_get('web_notifications_url', ''),
    '#size' => 90,
    '#maxlength' => 90,
    '#description' => t('URL to direct user'),
    '#required' => false,
  );

  $form['web_notifications_icon_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Icon URL'),
    '#default_value' => variable_get('web_notifications_icon_url', ''),
    '#size' => 90,
    '#maxlength' => 90,
    '#description' => t('Icon URL (http://www.example.com/iconss/icon.png)'),
    '#required' => false,
  );

  $form['web_notifications_body'] = array(
    '#type' => 'textarea',
    '#title' => t('body'),
    '#default_value' => variable_get('web_notifications_body', ''),
    '#size' => 50,
    '#maxlength' => 50,
    '#description' => t('Push Notification Body Text'),
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function web_notifications_sending_form_submit($form,$form_state){
  global $user;
  $user_id = $user->uid;

  $payload = $form_state['values']['web_notifications_title']  . '<br>';
  $payload .= $form_state['values']['web_notifications_body']  . '<br>';
  $payload .= $form_state['values']['web_notifications_icon_url']  . '<br>';
  $payload .= $form_state['values']['web_notifications_url']  . '<br>';

  web_notifications_send_message('0',$payload);
}
