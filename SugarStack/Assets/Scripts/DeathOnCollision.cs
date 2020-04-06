using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DeathOnCollision : MonoBehaviour {

	//referencing player scripts
	public CutTree cutTree; 
	public PlayerController playerController;
	public Image deathPanel;
	
	public GameObject restartMenu; //This is the restart menu obj

	void OnCollisionEnter2D (Collision2D obj)
	{
		Debug.Log("Hit");
		if(obj.gameObject.tag == "Branch" && !obj.gameObject.GetComponent<IsGrounded>().destroyed)
		{
			Debug.Log("Died");
			//trigger game over
			deathPanel.color = new Color32(212, 121, 105, 60); //Set color to red
			restartMenu.SetActive(true);
			cutTree.active = false; //freeze cutting
			playerController.active = false;//freeze movement
		}
	}
}
