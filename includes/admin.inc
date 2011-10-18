<?php

/**
 * @file
 * Contains administrative pages and functions for fieldable entity panes.
 */

function fieldable_panels_panes_entities_page() {
  $entity_info = entity_get_info('fieldable_panels_pane');

  $header = array(t('Name'), array('data' => t('Operations'), 'colspan' => 3));
  $rows = array();

  foreach ($entity_info['bundles'] as $bundle => $info) {
    $type_url_str = str_replace('_', '-', $bundle);

    $row = array();

    $label = check_plain($info['label']);
    $label .= ' <small>' . t('(Machine name: @type)', array('@type' => $bundle)) . '</small>';

    $row[] = $label;

    // Manage fields.
    $row[] = array('data' => l(t('list'), 'admin/structure/panels/entity/manage/' . $type_url_str));

    // Manage fields.
    $row[] = array('data' => l(t('manage fields'), 'admin/structure/panels/entity/manage/' . $type_url_str . '/fields'));

    // Display fields.
    $row[] = array('data' => l(t('manage display'), 'admin/structure/panels/entity/manage/' . $type_url_str . '/display'));

    $rows[] = $row;
  }

  $build['panes_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  return $build;
}

function fieldable_panels_panes_entities_list_page($type) {
  return t('The list page still needs to be implemented.');
}
