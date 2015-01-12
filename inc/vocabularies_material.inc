<?php
/**
 * @file
 * taxonomia_materiales.features.taxonomy.inc
 */

function materiales_vocabularies() {
  return array(
    'materiales' => array(
      'name' => 'Materiales',
      'machine_name' => 'materiales',
      'description' => 'Consumibles de la empresa',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
