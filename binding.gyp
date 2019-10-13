{
  "targets": [
    {
      "target_name": "node-refprop",
      "sources": [ "src/node-refprop.cpp", "src/thermostate.cpp" ],
      "include_dirs": [
				"<!(node -e \"require('nan')\")"
			]
    },
	{
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "node-refprop" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/node-refprop.node" ],
          "destination": "."
        }
      ]
    }
  ]
}