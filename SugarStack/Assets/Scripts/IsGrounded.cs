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
		if(obj.gameObject.tag == "floor")
		{
			this.gameObject.GetComponent<Rigidbody2D>().constraints = ~RigidbodyConstraints2D.FreezePositionX & ~RigidbodyConstraints2D.FreezePositionY;
			grounded = true;
		}
	}
}
