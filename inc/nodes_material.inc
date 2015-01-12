<?php
/**
 * @file
 * solicitud_material.features.inc
 */

/**
 * Implements hook_node_info().
 */
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
