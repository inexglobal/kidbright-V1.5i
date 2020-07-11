module.exports = function(Blockly){
'use strict';
// =============================================================================
//math Addiditon
// =============================================================================
Blockly.Blocks["math_single"] = {
	init: function () {
		this.jsonInit({
			"type": "math_single",
			"message0": "%1 %2",
			"args0": [{
					"type": "field_dropdown",
					"name": "OP",
					"options": [
						["%{BKY_MATH_SINGLE_OP_ROOT}", 'ROOT'],
						["%{BKY_MATH_SINGLE_OP_ABSOLUTE}", 'ABS'],
						['-', 'NEG'],
						['ln', 'LN'],
						['log10', 'LOG10'],
						['e^', 'EXP'],
						['10^', 'POW10']
					]
				},
				{
					"type": "input_value",
					"name": "NUM",
					"check": "Number"
				}
			],
			"output": "Number",
			"colour": Blockly.Msg.MATH_HUE,
			"helpUrl": "%{BKY_MATH_SINGLE_HELPURL}",
			"extensions": ["math_op_tooltip"]
		});
	}
}
Blockly.Blocks['math_trig'] = {
	init: function () {
		this.jsonInit({
			"type": "math_trig",
			"message0": "%1 %2",
			"args0": [{
					"type": "field_dropdown",
					"name": "OP",
					"options": [
						["%{BKY_MATH_TRIG_SIN}", "SIN"],
						["%{BKY_MATH_TRIG_COS}", "COS"],
						["%{BKY_MATH_TRIG_TAN}", "TAN"],
						["%{BKY_MATH_TRIG_ASIN}", "ASIN"],
						["%{BKY_MATH_TRIG_ACOS}", "ACOS"],
						["%{BKY_MATH_TRIG_ATAN}", "ATAN"]
					]
				},
				{
					"type": "input_value",
					"name": "NUM",
					"check": "Number"
				}
			],
			"output": "Number",
			"colour": Blockly.Msg.MATH_HUE,
			"helpUrl": "%{BKY_MATH_TRIG_HELPURL}",
			"extensions": ["math_op_tooltip"]
		});
	}
}
Blockly.Blocks['math_round'] = {
	init: function () {
		this.jsonInit({
			"type": "math_round",
			"message0": "%1 %2",
			"args0": [{
					"type": "field_dropdown",
					"name": "OP",
					"options": [
						["%{BKY_MATH_ROUND_OPERATOR_ROUND}", "ROUND"],
						["%{BKY_MATH_ROUND_OPERATOR_ROUNDUP}", "ROUNDUP"],
						["%{BKY_MATH_ROUND_OPERATOR_ROUNDDOWN}", "ROUNDDOWN"]
					]
				},
				{
					"type": "input_value",
					"name": "NUM",
					"check": "Number"
				}
			],
			"output": "Number",
			"colour": Blockly.Msg.MATH_HUE,
			"helpUrl": "%{BKY_MATH_ROUND_HELPURL}",
			"tooltip": "%{BKY_MATH_ROUND_TOOLTIP}"
		});
	}
}
Blockly.Blocks['math_random_int'] = {
	init: function () {
		this.jsonInit({
			"type": "math_random_int",
			"message0": "%{BKY_MATH_RANDOM_INT_TITLE}",
			"args0": [
				{
					"type": "field_number",
					"name": "FROM",
					"value": 0,
					"min": -9999999,
					"max": 9999999,
					"precision": 1
				  },
				{
					"type": "field_number",
					"name": "TO",
					"value": 100,
					"min": -9999999,
					"max": 9999999,
					"precision": 1
				  }
			],
			"inputsInline": true,
			"output": "Number",
			"colour": Blockly.Msg.MATH_HUE,
			"tooltip": "%{BKY_MATH_RANDOM_INT_TOOLTIP}",
			"helpUrl": "%{BKY_MATH_RANDOM_INT_HELPURL}"
		});
	}
}
Blockly.Blocks['math_pow'] = {
	init: function () {
		this.jsonInit({
			"type": "math_pow",
			"message0": "%1 " + Blockly.Msg.MATH_POW_TITLE + " %2",
			"args0": [{
					"type": "input_value",
					"name": "NUM1",
					"check": "Number"
				},
				{
					"type": "input_value",
					"name": "NUM2",
					"check": "Number"
				}
			],
			"inputsInline": true,
			"output": "Number",
			"colour": Blockly.Msg.MATH_HUE,
			"tooltip": Blockly.Msg.MATH_POW_TOOLTIP,
			"helpUrl": Blockly.Msg.MATH_POW_HELPURL
		});
	}
}
Blockly.Blocks['math_constrain'] = {
  /**
   * Block for constraining a number between two limits.
   * @this Blockly.Block
   */
  init: function() {
    this.jsonInit({
	  "type": "math_constrain",
      "message0": "constrain %1 low %2 high %3",
      "args0": [
        {
          "type": "input_value",
          "name": "VALUE",
          "check":"Number"
        },
        {
          "type": "input_value",
          "name": "LOW",
          "check": "Number"
        },
        {
          "type": "input_value",
          "name": "HIGH",
          "check": "Number"
        }
      ],
      "inputsInline": true,
	"output": "Number",
	"colour": Blockly.Msg.MATH_HUE,
	"tooltip": "Constrains a number to be within a range",
	"helpUrl": "https://www.arduino.cc/reference/en/language/functions/math/constrain/"
    });
  }
  //TODO: a getBlockType of the same type as the inputs.
}
Blockly.Blocks['math_map'] = {
  /**
   * Block for Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between.
   * @this Blockly.Block
   */
  init: function() {
    this.jsonInit({
	  "type": "math_map",
      "message0": "map%1fromLow%2fromHigh%3toLow%4toHigh%5",
      "args0": [
        {
          "type": "input_value",
          "name": "VALUE",
          "check":"Number"
        },
        {
          "type": "input_value",
          "name": "FROMLOW",
          "check": "Number"
        },
        {
          "type": "input_value",
          "name": "FROMHIGH",
          "check": "Number"
        },
        {
          "type": "input_value",
          "name": "TOLOW",
          "check": "Number"
        },
		{
          "type": "input_value",
          "name": "TOHIGH",
          "check": "Number"
        }
      ],
      "inputsInline": true,
	"output": "Number",
	"colour": Blockly.Msg.MATH_HUE,
	"tooltip": "Re-maps a number from one range to another",
	"helpUrl": "https://www.arduino.cc/reference/en/language/functions/math/map/"
    });
  }
  //TODO: a getBlockType of the same type as the inputs.
}
Blockly.Blocks['math_number_property'] = {
	init: function () {
		this.jsonInit({
			"type": "math_number_property",
			"message0": "%1 %2",
			"args0": [{
					"type": "input_value",
					"name": "NUMBER_TO_CHECK",
					"check": "Number"
				},
				{
					"type": "field_dropdown",
					"name": "PROPERTY",
					"options": [
						["%{BKY_MATH_IS_EVEN}", "EVEN"],
						["%{BKY_MATH_IS_ODD}", "ODD"],
						["%{BKY_MATH_IS_PRIME}", "PRIME"],
						["%{BKY_MATH_IS_POSITIVE}", "POSITIVE"],
						["%{BKY_MATH_IS_NEGATIVE}", "NEGATIVE"],
					]
				}
			],
			"inputsInline": true,
			"output": "Boolean",
			"colour": Blockly.Msg.MATH_HUE,
			"tooltip": "%{BKY_MATH_IS_TOOLTIP}",
			"mutator": "math_is_divisibleby_mutator"
		});
	}
}

Blockly.Blocks['convert_ra_de'] = {
	init: function () {
		this.jsonInit({
			"type": "convert_ra_de",
			"message0": "%{BKY_MATH_CONVERT_RA_DE_TITLE} %1 %2",
			"args0": [
			  {
				"type": "field_dropdown",
				"name": "OP",
				"options": [
				  [
					"%{BKY_MATH_CONVERT_RA_DE}",
					"RA_TO_DE"
				  ],
				  [
					"%{BKY_MATH_CONVERT_DE_RA}",
					"DE_TO_RA"
				  ]
				]
			  },
			  {
				"type": "input_value",
				"name": "NUM",
				"check": "Number"
			  }
			],
			"output": "Number",
			"colour": Blockly.Msg.MATH_HUE,
			"tooltip": "%{BKY_MATH_CONVERT_RA_DE_TOOLTIP}",
		});
	}
}
}