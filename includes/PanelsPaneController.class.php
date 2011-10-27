<?php
/**
 * @file
 *
 * Contains the controller class for the Fieldable Panel Pane entity.
 */

/**
 * Entity controller class.
 */
class PanelsPaneController extends DrupalDefaultEntityController {
  public $pane;

  public function attachLoad(&$queried_entities, $revision_id = FALSE) {
    parent::attachLoad($queried_entities, $revision_id);

    // We need to go through and unserialize our serialized fields.
    foreach ($queried_entities as $entity) {
      foreach (array('view_access', 'edit_access') as $key) {
        if (is_string($entity->$key)) {
          $entity->$key = unserialize($entity->$key);
        }
      }
    }
  }

  public function access($op, $entity = NULL, $account = NULL) {
    if ($op !== 'create' && !$entity) {
      return FALSE;
    }

    // The administer permission is a blanket override.
    if (user_access('administer fieldable panels panes')) {
      return TRUE;
    }

    switch ($op) {
      case 'create':
        return user_access('create fieldable panels panes');

      case 'view':
        ctools_include('context');
        return ctools_access($entity->view_access, fieldable_panels_panes_get_base_context($entity));

      case 'update':
        ctools_include('context');
        return user_access('edit fieldable panels panes') && ctools_access($entity->edit_access, fieldable_panels_panes_get_base_context($entity));

      case 'delete':
        ctools_include('context');
        return user_access('delete fieldable panels panes') && ctools_access($entity->edit_access, fieldable_panels_panes_get_base_context($entity));

    }

    return FALSE;
  }

  public function save($pane) {
    $pane = (object) $pane;
    $transaction = db_transaction();

    field_attach_presave('fieldable_panels_pane', $pane);

    try {
      if (isset($pane->fpid) && is_numeric($pane->fpid)) {
        drupal_write_record('fieldable_panels_panes', $pane, 'fpid');
        field_attach_update('fieldable_panels_pane', $pane);
      }
      else {
        drupal_write_record('fieldable_panels_panes', $pane);
        field_attach_insert('fieldable_panels_pane', $pane);
      }

      return $pane;
    }
    catch (Exception $e) {
      $transaction->rollback('fieldable_panels_panes');
      watchdog_exception('fieldable_panels_panes', $e);
      throw $e;
    }

    return FALSE;
  }

  public function view($pane, $view_mode = 'full', $langcode = NULL) {
    // attach our fields and prepare the pane for rendering
    field_attach_prepare_view('fieldable_panels_pane', array($pane->fpid => $pane), $view_mode, $langcode);
    entity_prepare_view('fieldable_panels_pane', array($pane->fpid => $pane), $langcode);
    $pane->content = field_attach_view('fieldable_panels_pane', $pane, $view_mode, $langcode);
    $pane->content += array(
      '#theme' => 'fieldable_panels_pane',
      '#element' => $pane,
      '#view_mode' => $view_mode,
      '#language' => $langcode,
    );

    return drupal_render($pane->content);
  }

  public function delete($fpids) {
    $transaction = db_transaction();
    if (!empty($fpids)) {
      $entities = fieldable_panels_panes_load_multiple($fpids, array());

      try {
        foreach ($entities as $fpid => $node) {
          // Call the node-specific callback (if any):
          module_invoke_all('entity_delete', $node, 'fieldable_panels_pane');
          field_attach_delete('fieldable_panels_pane', $node);
        }

        // Delete after calling hooks so that they can query node tables as needed.
        db_delete('fieldable_panels_panes')
          ->condition('fpid', $fpids, 'IN')
          ->execute();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception('fieldable_panels_pane', $e);
        throw $e;
      }

      // Clear the page and block and node_load_multiple caches.
      entity_get_controller('fieldable_panels_pane')->resetCache();
    }
  }

  public function create($values) {
    $entity = (object) array(
      'bundle' => $values['bundle'],
      'language' => LANGUAGE_NONE,
      'is_new' => TRUE,
    );

    // Ensure basic fields are defined.
    $values += array(
      'bundle' => 'fieldable_panels_pane',
      'title' => '',
      'reusable' => FALSE,
      'admin_title' => '',
      'admin_description' => '',
      'category' => '',
    );

    // Apply the given values.
    foreach ($values as $key => $value) {
      $entity->$key = $value;
    }

    return $entity;
  }

}
