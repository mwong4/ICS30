using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {

	public bool atRight;

	// Use this for initialization
	void Start () {
		transform.position = new Vector2(7,-3);
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.RightArrow) && atRight == false) //If player is on left and chooses to go right
		{
			transform.position = new Vector2(7,-3); //Change position to right
			transform.rotation = Quaternion.Euler(Vector3.up * 180); //Rotate to face into center
			atRight = true; //Update variable
		}
		else if(Input.GetKeyDown(KeyCode.LeftArrow) && atRight == true) //If player is on right and chooses to go left
		{
			transform.position = new Vector2(-7,-3); //Change position to left
			transform.rotation = Quaternion.Euler(Vector3.up * 360); //Rotate to face into center
			atRight = false; //Update variable
		}
	}
}
