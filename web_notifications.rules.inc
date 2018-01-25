<?php

/**
 * Implements hook_rules_action_info().
 */
function web_notifications_rules_action_info() {
  $items = array();

  $items['web_notifications_send_message_bulk'] = array(
    'label' => t('Send a Web notification to all registered tokens'),
    'group' => t('Web notification'),
    'parameter' => array(
      'payload' => array(
        'type' => 'text',
        'label' => t('Notification message'),
      ),
    ),
  );

  return $items;
}

function web_notifications_send_message_bulk($payload) {
  web_notifications_send_message('0',$payload);
}
