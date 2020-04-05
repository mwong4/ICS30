using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsGrounded : MonoBehaviour {

	public bool grounded; //boolean to tell if grounded

	void start()
	{
		grounded = false; //originally no
	}

	//To tell if grounded
	void OnCollisionEnter2D (Collision2D obj)
	{
		Debug.Log("Collision");
		if(obj.gameObject.tag == "floor")
		{
			Debug.Log("Updated");
			grounded = true;
		}
	}
}
