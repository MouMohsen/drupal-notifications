<?php

require  'vendor/autoload.php';
use Minishlink\WebPush\WebPush;

/**
* Page callback: Web Notifications sending form
*
* @see web_notifications_menu()
*/
function web_notifications_sending_form($form, &$form_state) {

  // Build the sortable table header.
// $header = array(
//  'endpoint' => t('Endpoint'),
//  'token' => t('Token'),
//  'public_key' => t('Public Key'),
// );

// $query = db_select('web_notifications','web')->extend('pagerDefault');
// $query
//     ->fields('web', array('endpoint', 'token', 'public_key'))
//     ->limit(25);
//     $results = $query->execute();
//
//     foreach ($results as $result ) {
//
//     $rows = array();
//     $rows[]= array(
//       'endpoint' => $result->endpoint,
//       'token' => $result->token,
//       'public_key' =>$result->public_key,
//       '#attributes' => array('class'=> array('subscriptions-row')),
//     );
//     }

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

  // $form['web_notifications_table'] = array(
  //   '#type' => 'tableselect',
  //   '#header' => $header,
  //   '#options' => $rows,
  //   '#empty' => t('No subscriptions Found'),
  //   '#attributes' => array('class' => array('subscriptions')),
  // );
  //
  // $form['pager'] = array(
  //   '#markup' => theme('pager')
  // );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function web_notifications_sending_form_submit($form,$form_state){
      global $user;
      $user_id = $user->uid;
      dpm ($user_id);

  $payload = $form_state['values']['web_notifications_title']  . '<br>';
  $payload .= $form_state['values']['web_notifications_body']  . '<br>';
  $payload .= $form_state['values']['web_notifications_icon_url']  . '<br>';
  $payload .= $form_state['values']['web_notifications_url']  . '<br>';

  $query = db_select('web_notifications_endpoints', 'v');
  $query->fields('v',array('endpoint','token','public_key'));
  $result = $query->execute();
  while($subscription = $result->fetchAssoc()) {
    $auth = array(
      'VAPID' => array(
        'subject' => 'https://enty.tv/',
        'publicKey' => 'BGH_Q1P5l5jqs7sFmww0drnW-v9xJlTY5UYGrb1zaAhAqbe278saTwZCXR6KYG9mrI_-6TISV4dkv0AICX2Ojas',
        'privateKey' => '9vtMiDZij0G2dgosVLPPBD3E1mrPHyVcaiq6GN155a0',
      ),
    );
$webPush = new WebPush($auth);
$res = $webPush->sendNotification(
  $subscription["endpoint"],
  $payload,
  $subscription["public_key"],
  $subscription["token"]
);
    }
$webPush->flush();


 //  } else {
 //    echo "No Endpoints found";
 //  }
 //
 //  $conn->close();
 //  //Redirect
 //  header('Location: ' . $_SERVER['HTTP_REFERER']);

}
