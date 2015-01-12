<?php
/**
 * @file
 * solicitud_material.features.inc
 */

/**
 * Implements hook_node_info().
 */

/*
function material_node_info() {
  $items = array(
    'solicitud_material' => array(
      'name' => t('Solicitud material'),
      'base' => 'node_content',
      'description' => '',
      //'has_title' => '1',
      //'title_label' => t('Title'),
      //'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
*/



function crear_tipos_nodo(){
  /*
  ** CREAMOS EL NODO
  */

  // Insert default pre-defined node types into the database. For a complete
  // list of available node type attributes, refer to the node type API
  // documentation at: http://api.drupal.org/api/HEAD/function/hook_node_info.

  // http://www.sitepoint.com/creating-a-new-drupal-node-type/
  $t = get_t(); // runs in both the installer and runtime

  $nodeTypes = array(
    array(
      'type' => 'solicitud_material',
      'name' => $t('Solicitud material'),// Display name of the content type
      'base' => 'node_content',
      'title_label' => $t('Titulo'),
      'description' => $t('Para solicitar material.'),
      'custom' => FALSE,
      //'modified' => 1,
      //'locked' => 0,
    ),

  );

  foreach ($nodeTypes as $nodeType) {
    $nodeType = node_type_set_defaults($nodeType);

    // añade body
    //node_add_body_field($type);

    node_type_save($nodeType);

  }


   // OPCIONES NODO
   // Turn off comments
   variable_set('comment_solicitud_material', '1');

   // display author an date
   variable_set('comment_subject_field_solicitud_material', 1);

}


// llamamos a la funcion

crear_tipos_nodo();