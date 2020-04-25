using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelfDestruct : MonoBehaviour {

	private float curTime;

	// Use this for initialization
	void Start () {
		//Destroy(this.gameObject, 15f);
		curTime = 0;
	}

	void update()
	{
		if(curTime < 20)
		{
			curTime += Time.deltaTime;
		}
		if(curTime > 15 && curTime < 16)
		{
			//this.gameObject.active = false;
		}
	}
}
