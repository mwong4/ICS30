using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	public bool atRight; //this tracks player position
	public bool active; //this tracks if movement is frozen

	// Use this for initialization
	void Start () {
		transform.position = new Vector2(4,-3);
		atRight = true;
		active = true;
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.RightArrow) && !atRight && active) //If player is on left and chooses to go right
		{
			transform.position = new Vector2(4,-3); //Change position to right
			transform.rotation = Quaternion.Euler(Vector3.up * 180); //Rotate to face into center
			atRight = true; //Update variable
		}
		else if(Input.GetKeyDown(KeyCode.LeftArrow) && atRight && active) //If player is on right and chooses to go left
		{
			transform.position = new Vector2(-4,-3); //Change position to left
			transform.rotation = Quaternion.Euler(Vector3.up * 360); //Rotate to face into center
			atRight = false; //Update variable
		}
	}
}
