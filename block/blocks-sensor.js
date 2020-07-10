module.exports = function(Blockly){
'use strict';
// =============================================================================
// sensor
// =============================================================================
var sensor_colour= Blockly.Msg.SENSOR_HUE ;
const dirIcon = Vue.prototype.$global.board.board_info.dir;
// var sensor_colour="#CAC745";

Blockly.Blocks["sensor_lm73"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage("/static/block_icons/sot23-6_1.png", 20, 20, "*"))
			.appendField(Blockly.Msg.SENSOR_LM73_TITLE);
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(sensor_colour);
		this.setTooltip(Blockly.Msg.SENSOR_LM73_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SENSOR_LM73_HELPURL);
	}
};

Blockly.Blocks["sensor_ldr"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage("/static/block_icons/ldr1.png", 20, 20, "*"))
			.appendField(Blockly.Msg.SENSOR_LDR_TITLE);
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(sensor_colour);
		this.setTooltip(Blockly.Msg.SENSOR_LDR_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SENSOR_LDR_HELPURL);
	}
};

Blockly.Blocks["sensor_switch1"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage("/static/block_icons/sw12x12.png", 20, 20, "*"))
			.appendField(Blockly.Msg.SENSOR_SWITCH1_TITLE);
		this.setOutput(true, ['Number','Boolean']);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(sensor_colour);
		this.setTooltip(Blockly.Msg.SENSOR_SWITCH1_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SENSOR_SWITCH1_HELPURL);
	}
};

Blockly.Blocks["sensor_switch2"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage("/static/block_icons/sw12x12.png", 20, 20, "*"))
			.appendField(Blockly.Msg.SENSOR_SWITCH2_TITLE);
		this.setOutput(true, ['Number','Boolean']);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(sensor_colour);
		this.setTooltip(Blockly.Msg.SENSOR_SWITCH2_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SENSOR_SWITCH2_HELPURL);
	}
};
Blockly.Blocks['acc_read'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage(`file:///${dirIcon}/static/xyz1.png`, 20, 20, "*"))
			.appendField("acceleration")
			.appendField(new Blockly.FieldDropdown([["x","0"], ["y","1"], ["z","2"],["Strength","3"]]), "axes");
		this.setOutput(true, ['Number']);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(sensor_colour);
		this.setTooltip("Read acceleration");
		this.setHelpUrl("");
	}
};
Blockly.Blocks["compass_read"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage(`file:///${dirIcon}/static/comp.png`, 20, 20, "*"))
			.appendField("compass heading ( ° )");
		this.setOutput(true, ['Number']);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(sensor_colour);
		this.setTooltip("Read compass");
		this.setHelpUrl("");
	}
};
Blockly.Blocks["calibrateCompass"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage(`file:///${dirIcon}/static/comp.png`, 20, 20, "*"))
			.appendField("calibrateCompass");
		//this.setOutput(true, ['Number']);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(sensor_colour);
		this.setTooltip("calibrate Compass");
		this.setHelpUrl("");
	}
};
Blockly.Blocks["calibrateAcc"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage(`file:///${dirIcon}/static/comp.png`, 20, 20, "*"))
			.appendField("calibrateAcc");
		//this.setOutput(true, ['Number']);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(sensor_colour);
		this.setTooltip("calibrate Acc");
		this.setHelpUrl("");
	}
};
/*
Blockly.Blocks['compass_read'] = {
	init: function() {
		this.jsonInit({
			"type": "compass_read",
			"message0": "%1 compass heading ( ° )",
						"args0": [{
						  "type": "field_image",
						  "src": `file:///${dirIcon}/static/comp.png`,
						  "width": 20,
						  "height": 20,
						  "alt": "*"
						}],
			"output": "Number",
			"colour": 58,
			"tooltip": "Read compass",
			"helpUrl": ""
		});
	}
};
*/
};