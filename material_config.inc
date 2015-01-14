<?php


/**
	FORMULARI CONFIGURACIO 
**/


/**
 * Page callback: Current posts settings
 *
 * @see current_posts_menu()
 */


function material_config_form($form, &$form_state) {

	/*
	$rolesUsuarios =  user_roles(TRUE);
	array_unshift($rolesUsuarios, "");

	$form['role_material'] = array(
	   '#type' => 'select',
	    '#title' => t('Role para visualizar solicitudes material'),
	    '#options' => $rolesUsuarios,
	    '#default_value' => variable_get('role_material'),
	    '#description' => t('Selecciona el role que podrà gestionar los permisos de vacaciones.'),
		'#required' => FALSE,	
	);

	*/

  $users = entity_load('user');

  $mailNameUsers = array();

  foreach ($users as $user) {

  	$mailNameUsers[$user->mail] = $user->name;

  }


  $form['mail_material'] = array(
	   '#type' => 'select',
	    '#title' => t('Usuario que recibirà las notificaciones de solicitudes de material'),
	    '#options' => $mailNameUsers,
	    '#default_value' => variable_get('mail_material'),
	    '#description' => t('Selecciona el usuario que recibirà los mails de pedido de material.'),
    	'#required' => FALSE,	
  	);


/*
    $form['any_vacances'] = array(
	   '#type' => 'textfield',
	    '#title' => t('Any actual'),
	    '#disabled' => TRUE,
	    //'#access' => FALSE,
	    '#default_value' => variable_get('any_vacances'),
	    '#description' => t('Guarda la configuración para actualitzar este campo.'),
    	'#required' => FALSE,	
  	);
*/




  //$form['#submit'][] = 'vacances_config_submit';

  return system_settings_form($form);


}