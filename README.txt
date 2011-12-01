Fieldable Panel Panes support multiple bundles, but at this time there is no
UI to create bundles.

Bundles can be created in a module via hook_entity_info_alter(). The code
will look something like this:

function MYMODULE_entity_info_alter(&$entity_info) {
  $entity_info['fieldable_panels_pane']['bundles']['my_bundle_name'] = array(
      'label' => t('My bundle name'),
      'admin' => array(
        'path' => 'admin/structure/panels/entity/manage/%fieldable_panels_panes_type',
        'bundle argument' => 5,
        // Note that this has all _ replaced with - from the bundle name.
        'real path' => 'admin/structure/panels/entity/manage/my-bundle-name',
        'access arguments' => array('administer fieldable panels panes'),
      ),
    ),
  );
}
