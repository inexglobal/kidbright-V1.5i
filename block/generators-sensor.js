module.exports = function(Blockly){
'use strict';
// =============================================================================
// sensor
// =============================================================================
Blockly.JavaScript['sensor_lm73'] = function(block) {
	//var code = 'lm73.readTemp()\n';
	//return code;
	return [
		'lm73.readTemp()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['sensor_ldr'] = function(block) {
	return [
		'ldr.mapLDR()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['sensor_switch1'] = function(block) {
	return [ '((int)digitalRead(KB_BUTTON1))',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['sensor_switch2'] = function(block) {
	return [ '((int)digitalRead(KB_BUTTON2))',
		// 'button12.sw2_get()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};
/*
Blockly.JavaScript['acc_read'] = function(block) {
	var axes = block.getFieldValue('axes');
	var WIRE_OBJ = 'Wire';
	var SDA_PIN = 21, SCL_PIN = 22; 

	var board_name = Vue.prototype.$global.board.board_info.name;
	if (board_name == 'kidbright-arduino' || board_name == 'openkb'|| board_name == 'kidbright-V1.5i') {
		WIRE_OBJ = 'Wire1';
		SDA_PIN = 4;
		SCL_PIN = 5;
	} else if (board_name == 'ipst-wifi') {

	}

	var code = '';
	code += `#EXTINC#include <Wire.h>#END\n`;
	code += `#EXTINC#include <LSM303AGR_ACC_Sensor.h>#END\n`;
	code += `#EXTINC#include <LSM303AGR_MAG_Sensor.h>#END\n`;
	code += `#VARIABLE LSM303AGR_ACC_Sensor *Acc;#END\n`;
	code += `#VARIABLE LSM303AGR_ACC_Sensor *Acc;#END\n`;
	//code += `#VARIABLE Acc = new LSM303AGR_ACC_Sensor(&${WIRE_OBJ}); #END\n`;
    code += `#SETUP ${WIRE_OBJ}.begin(${SDA_PIN}, ${SCL_PIN}); #END`;
	code += `#SETUP Acc = new LSM303AGR_ACC_Sensor(&${WIRE_OBJ}); #END`;
    code += `#SETUP Acc->Enable();#END`;
	//code += `#LOOP_CODE int32_t accelerometer[3]; #END\n`;
	//code += `#LOOP_CODE Acc->GetAxes(accelerometer); #END\n`;
	//code += `accelerometer[${axes}]`;
	code += `Acc->GetAxes_xyz(${axes})`;
	return [code, Blockly.JavaScript.ORDER_NONE];
	};
*/	
Blockly.JavaScript['acc_read'] = function(block) {
	var axes = block.getFieldValue('axes');
	var WIRE_OBJ = 'Wire';
	var SDA_PIN = 21, SCL_PIN = 22; 

	var board_name = Vue.prototype.$global.board.board_info.name;
	if (board_name == 'kidbright-arduino' || board_name == 'openkb'|| board_name == 'kidbright-V1.5i') {
		WIRE_OBJ = 'Wire1';
		SDA_PIN = 4;
		SCL_PIN = 5;
	} else if (board_name == 'ipst-wifi') {

	}

	var code = '';
	code += `imu.get_acc_xyz(${axes})`;
	return [code, Blockly.JavaScript.ORDER_NONE];
	};
/*
Blockly.JavaScript['compass_read'] = function(block) {
	var axes = block.getFieldValue('axes');
	var WIRE_OBJ = 'Wire';
	var SDA_PIN = 21, SCL_PIN = 22; 

	var board_name = Vue.prototype.$global.board.board_info.name;
	if (board_name == 'kidbright-arduino' || board_name == 'openkb'|| board_name == 'kidbright-V1.5i') {
		WIRE_OBJ = 'Wire1';
		SDA_PIN = 4;
		SCL_PIN = 5;
	} else if (board_name == 'ipst-wifi') {

	}

	var code = '';
	code += `#EXTINC#include <Wire.h>#END\n`;
	code += `#EXTINC#include <LSM303AGR_ACC_Sensor.h>#END\n`;
	code += `#EXTINC#include <LSM303AGR_MAG_Sensor.h>#END\n`;
	code += `#VARIABLE LSM303AGR_ACC_Sensor *Acc;#END\n`;
	code += `#VARIABLE LSM303AGR_ACC_Sensor *Acc;#END\n`;
	//code += `#VARIABLE Acc = new LSM303AGR_ACC_Sensor(&${WIRE_OBJ}); #END\n`;
    code += `#SETUP ${WIRE_OBJ}.begin(${SDA_PIN}, ${SCL_PIN}); #END`;
	code += `#SETUP Acc = new LSM303AGR_ACC_Sensor(&${WIRE_OBJ}); #END`;
    code += `#SETUP Acc->Enable();#END`;
	//code += `#LOOP_CODE int32_t accelerometer[3]; #END\n`;
	//code += `#LOOP_CODE Acc->GetAxes(accelerometer); #END\n`;
	//code += `accelerometer[${axes}]`;
	code += `Acc->GetAxes_xyz(${axes})`;
	return [code, Blockly.JavaScript.ORDER_NONE];

	//return code;
	};
};
*/
Blockly.JavaScript['compass_read'] = function(block) {
	var axes = block.getFieldValue('axes');
	var WIRE_OBJ = 'Wire';
	var SDA_PIN = 21, SCL_PIN = 22; 

	var board_name = Vue.prototype.$global.board.board_info.name;
	if (board_name == 'kidbright-arduino' || board_name == 'openkb'|| board_name == 'kidbright-V1.5i') {
		WIRE_OBJ = 'Wire1';
		SDA_PIN = 4;
		SCL_PIN = 5;
	} else if (board_name == 'ipst-wifi') {

	}

	var code = '';
	code += `imu.get_heading()`;
	return [code, Blockly.JavaScript.ORDER_NONE];
	};

Blockly.JavaScript['calibrateCompass'] = function(block) {
	var axes = block.getFieldValue('axes');
	var WIRE_OBJ = 'Wire';
	var SDA_PIN = 21, SCL_PIN = 22; 

	var board_name = Vue.prototype.$global.board.board_info.name;
	if (board_name == 'kidbright-arduino' || board_name == 'openkb'|| board_name == 'kidbright-V1.5i') {
		WIRE_OBJ = 'Wire1';
		SDA_PIN = 4;
		SCL_PIN = 5;
	} else if (board_name == 'ipst-wifi') {

	}

	var code = '';
	code += `imu.calibrate_compass();`;
	return code;
	};
Blockly.JavaScript['calibrateAcc'] = function(block) {
	var axes = block.getFieldValue('axes');
	var WIRE_OBJ = 'Wire';
	var SDA_PIN = 21, SCL_PIN = 22; 

	var board_name = Vue.prototype.$global.board.board_info.name;
	if (board_name == 'kidbright-arduino' || board_name == 'openkb'|| board_name == 'kidbright-V1.5i') {
		WIRE_OBJ = 'Wire1';
		SDA_PIN = 4;
		SCL_PIN = 5;
	} else if (board_name == 'ipst-wifi') {

	}

	var code = '';
	code += `imu.calibrate_acc();`;
	return code;
	};
};