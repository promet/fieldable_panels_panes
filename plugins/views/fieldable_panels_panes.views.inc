<?php

/**
 * @file
 * Provides views integration for fieldable panels panes.
 */

/**
 * Implements hook_views_data().
 */
function fieldable_panels_panes_views_data() {
  $data = array();

  // ------------------------------------------------------------------------
  // RCME Address
  $data['fieldable_panels_panes'] = array(
    'table' => array(
      'base' => array(
        'field' => 'fpid',
        'title' => t('Fieldable pane entity'),
        'help' => t('A fieldable panel pane entity.'),
      ),
      'group' => t('Fieldable pane'),
      'entity type' => 'fieldable_panels_pane',
    ),
    'fpid' => array(
      'title' => t('Fieldable pane ID'),
      'help' => t('The internal ID of the pane.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'bundle' => array(
      'title' => t('Bundle'),
      'help' => t('The bundle (type) of the entity.'),
      'field' => array(
        'handler' => 'fieldable_panels_panes_handler_field_bundle',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'fieldable_panels_panes_handler_filter_bundle',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'fieldable_panels_panes_handler_argument_bundle',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'title' => array(
      'title' => t('Title'),
      'help' => t('The content title of the entity.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'admin_title' => array(
      'title' => t('Administrative title'),
      'help' => t('The administrative title of the entity.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'admin_description' => array(
      'title' => t('Administrative description'),
      'help' => t('The administrative description of the entity.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'category' => array(
      'title' => t('Administrative category'),
      'help' => t('The administrative category of the entity.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_string',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_string',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'reusable' => array(
      'title' => t('Reusable'),
      'help' => t('Is this entity reusable and available to add to panels via the Add Content pane.'),
      'field' => array(
        'handler' => 'views_handler_field_boolean',
        'click sortable' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_boolean_operator',
        'allow empty' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
      ),
      'sort' => array(
        'handler' => 'views_handler_sort',
      ),
    ),
    'view_entity' => array(
      'field' => array(
        'title' => t('Administrative link'),
        'help' => t('Provide a simple link for administrators to view the content.'),
        'handler' => 'fieldable_panels_panes_handler_field_view_entity',
      ),
    ),
    'edit_entity' => array(
      'field' => array(
        'title' => t('Administrative edit link'),
        'help' => t('Provide a simple link for administrators to edit the content.'),
        'handler' => 'fieldable_panels_panes_handler_field_edit_entity',
      ),
    ),
    'delete_entity' => array(
      'field' => array(
        'title' => t('Administrative delete link'),
        'help' => t('Provide a simple link for administrators to delete the content.'),
        'handler' => 'fieldable_panels_panes_handler_field_delete_entity',
      ),
    ),
  );

  return $data;
}
