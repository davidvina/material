<?php

/**
  Implements hook_views_api().
*/


// carga todas las views que se encuentran en la carpeta de views


 function material_views_default_views() {

  //$module_name = basename(__FILE__, '.module');

  // Check for all view file in views directory
  $files = file_scan_directory(drupal_get_path('module', 'material') . '/views', '/.*\.inc$/');

  $views = array();

  // Add view to list of views
  foreach ($files as $filepath => $file) {
    require $filepath;
    if (isset($view)) {
      $views[$view->name] = $view;
    }
  }

  // At the end, return array of default views.
  return $views;
}
