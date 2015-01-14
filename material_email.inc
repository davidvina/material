<?php

/*
  Construccion del mensage

*/

$mensage = array();

// get variable email
$mensage['email'] = variable_get('mail_material');

// construir mensage
// extraemos todos los nodos que estan publicados del tipo solicitud_material
//$type = "solicitud_material";
$nodes = node_load_multiple(array(), array('type' => 'solicitud_material', 'status' => 1));

//dpm($nodes);



$mensage['message'] = "<h2>".t('Solicitud material')."</h2>";
$mensage['message'] = "<table border='1' cellpadding='5' cellspacing='0'>";
$mensage['message'] .= "<tr>";
$mensage['message'] .= "<th>Material </th><th>Cantidad </th><th>Solicitante </th><th>Fecha solicitud </th>";
$mensage['message'] .= "</tr>";


foreach ($nodes as $key => $node) {

  // recogemos autor del nodo
  $autorNodo = user_load($node->uid);

  // formateamos fecha pedido
  $formatted_date = format_date($node->created, 'custom', 'D d/m/y - G:i');

  $mensage['message'] .= "<tr>";
  $mensage['message'] .= "<td>". $node->title."</td><td>". $node->field_cantidad['und'][0]['value']."</td><td>".$autorNodo->name."</td><td>".$formatted_date."</td>";
  $mensage['message'] .= "</tr>";

}

$mensage['message'] .= "</table>";


material_mail_send($mensage);


/**
 * Implement hook_mail().
 *
 * This hook defines a list of possible e-mail templates that this module can
 * send. Each e-mail is given a unique identifier, or 'key'.
 *
 * $message comes in with some standard properties already set: 'to' address,
 * 'from' address, and a set of default 'headers' from drupal_mail(). The goal
 * of hook_mail() is to set the message's 'subject' and 'body' properties, as
 * well as make any adjustments to the headers that are necessary.
 *
 * The $params argument is an array which can hold any additional data required
 * to build the mail subject and body; for example, user-entered form data, or
 * some context information as to where the mail request came from.
 *
 * Note that hook_mail() is not actually a hook. It is only called for a single
 * module, the module named in the first argument of drupal_mail(). So it's
 * a callback of a type, but not a hook.
 */
function material_mail($key, &$message, $params) {
  //global $user;


  // Set the mail content type to html to send an html e-mail (optional).
  $message['headers']['Content-Type'] = 'text/html; charset=UTF-8; format=flowed';

  // Each message is associated with a language, which may or may not be the
  // current user's selected language, depending on the type of e-mail being
  // sent. This $options array is used later in the t() calls for subject
  // and body to ensure the proper translation takes effect.
  $options = array(
    'langcode' => $message['language']->language,
  );

  switch ($key) {
    // Send a simple message from the contact form.
    case 'material_message':

      $fecha = date('d-m-y');
      $message['subject'] = t('Solicitud de material | @time', array('@time' => $fecha), $options);

      // Note that the message body is an array, not a string.
      //$message['body'][] = t('@name sent you the following message:', array('@name' => $user->name), $options);
      // Because this is just user-entered text, we do not need to translate it.

      // Since user-entered text may have unintentional HTML entities in it like
      // '<' or '>', we need to make sure these entities are properly escaped,
      // as the body will later be transformed from HTML to text, meaning
      // that a normal use of '<' will result in truncation of the message.
      $message['body'][] = check_plain($params['message']);
      break;
  }
}

/**
 * Send an e-mail.
 *
 * @param $form_values
 *   An array of values from the contact form fields that were submitted.
 *   There are just two relevant items: $form_values['email'] and
 *   $form_values['message'].
 */
function material_mail_send($form_values) {
  // All system mails need to specify the module and template key (mirrored from
  // hook_mail()) that the message they want to send comes from.
  $module = 'material';
  $key = 'material_message';

  // Specify 'to' and 'from' addresses.
  $to = $form_values['email'];
  //$from = variable_get('site_mail', 'admin@example.com');
  $from = 'iptecno@iptecno.com';

  // "params" loads in additional context for email content completion in
  // hook_mail(). In this case, we want to pass in the values the user entered
  // into the form, which include the message body in $form_values['message'].
  $params = $form_values;

  // The language of the e-mail. This will one of three values:
  // * user_preferred_language(): Used for sending mail to a particular website
  //   user, so that the mail appears in their preferred language.
  // * global $language: Used when sending a mail back to the user currently
  //   viewing the site. This will send it in the language they're currently
  //   using.
  // * language_default(): Used when sending mail to a pre-existing, 'neutral'
  //   address, such as the system e-mail address, or when you're unsure of the
  //   language preferences of the intended recipient.
  //
  // Since in our case, we are sending a message to a random e-mail address that
  // is not necessarily tied to a user account, we will use the site's default
  // language.
  $language = language_default();

  // Whether or not to automatically send the mail when drupal_mail() is
  // called. This defaults to TRUE, and is normally what you want unless you
  // need to do additional processing before drupal_mail_send() is called.
  $send = TRUE;
  // Send the mail, and check for success. Note that this does not guarantee
  // message delivery; only that there were no PHP-related issues encountered
  // while sending.
  $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);

  if ($result['result'] == TRUE) {
    drupal_set_message(t('Solicitud de material enviada.'));
  }
  else {
    drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
  }

}


