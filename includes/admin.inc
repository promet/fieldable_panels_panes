<?php

/**
 * @file
 * Contains administrative pages and functions for fieldable entity panes.
 */

/**
 * List all bundles and administrative options for entity panes.
 */
function fieldable_panels_panes_entities_page() {
  $entity_info = entity_get_info('fieldable_panels_pane');

  $header = array(t('Name'), array('data' => t('Operations'), 'colspan' => 2));
  $rows = array();

  foreach ($entity_info['bundles'] as $bundle => $info) {
    $type_url_str = str_replace('_', '-', $bundle);

    $row = array();

    $label = check_plain($info['label']);
    $label .= ' <small>' . t('(Machine name: @type)', array('@type' => $bundle)) . '</small>';

    $row[] = $label;

    $operations = array();

    $operations['list'] = array(
      'title' => t('list'),
      'href' => 'admin/structure/panels/entity/manage/' . $type_url_str,
    );

    $operations['add'] = array(
      'title' => t('add'),
      'href' => 'admin/structure/panels/entity/manage/' . $type_url_str . '/add',
    );

    $operations['fields'] = array(
      'title' => t('manage fields'),
      'href' => 'admin/structure/panels/entity/manage/' . $type_url_str . '/fields',
    );

    $operations['display'] = array(
      'title' => t('manage display'),
      'href' => 'admin/structure/panels/entity/manage/' . $type_url_str . '/display',
    );

    $ops = theme('links', array('links' => $operations, 'attributes' => array('class' => array('links', 'inline'))));

    $row[] = $ops;
    $rows[] = $row;
  }

  $build['panes_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  return $build;
}

/**
 * List all entities for the given type.
 */
function fieldable_panels_panes_entities_list_page($type) {
  return t('The list page still needs to be implemented.');
}

/**
 * Page callback to add a new pane entity.
 */
function fieldable_panels_panes_entities_add_page($type) {
  $form_state = array(
    'entity' => fieldable_panels_pane_create(array('bundle' => $type)),
    'add submit' => TRUE,
  );

  return drupal_build_form('fieldable_panels_panes_entity_edit_form', $form_state);
}

/**
 * Page callback to view a entity.
 *
 * This represents an administrative view only. It is not available to
 * the general public. These entities are meant to be viewed as panel
 * panes (or blocks).
 */
function fieldable_panels_panes_entity_view_page($entity) {
  return fieldable_panels_pane_view($entity);
}

/**
 * Page callback to view a entity.
 */
function fieldable_panels_panes_entity_edit_page($entity) {
  $form_state = array(
    'entity' => $entity,
    'add submit' => TRUE,
  );

  return drupal_build_form('fieldable_panels_panes_entity_edit_form', $form_state);
}
