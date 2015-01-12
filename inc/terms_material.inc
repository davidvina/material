<?php

function terms_materiales(){

	$terms = array();

	$terms[] = "Otros";
	$terms[] = "Capsa Petita 395x265x191";
	$terms[] = "Capsa Mitjana 380x320x240";
	$terms[] = "Capsa Gran 440x365x320";
	$terms[] = "Toner Magatzem EPSON M1200";
	$terms[] = "Toner Magatzem HP C4096A";
	$terms[] = "Toner Comercials HP CB436A";
	$terms[] = "Toner Enric HP C4096A";
	$terms[] = "Toner Fax Brother TN2210";
	$terms[] = "Precinto";
	$terms[] = "Fleje";
	$terms[] = "Film Negro";
	$terms[] = "Film Transparente";

	return $terms;
}


//  Taxonomy dupecheck
//  https://www.drupal.org/project/taxonomy_dupecheck

function crear_terminos($newTerms, $vocabularyName){

	//get vocabulary id

	if($vocabulary = taxonomy_vocabulary_machine_name_load($vocabularyName)){

		foreach ($newTerms as $newTerm) {


			// extraemos array con terminos que coinciden
			$coincidencias = taxonomy_get_term_by_name($newTerm);

			// si exite termino
			if(count($coincidencias)>0){
				foreach ($coincidencias as $key => $value) {

					// actualizamos termino
					taxonomy_term_save((object) array(
					  'tid' => $key,
					  'name' => $newTerm,
					  'vid' => $vocabulary->vid,
					));

				}
			
			}
			// no existe termino
			else {
				taxonomy_term_save((object) array(
				  'name' => $newTerm,
				  'vid' => $vocabulary->vid,
				));
			}


		}


	}

}

$listaMateriales = terms_materiales();
crear_terminos($listaMateriales, 'materiales');