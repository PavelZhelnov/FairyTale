function nextPhoto()
{
	if (current < num)
	{
			current++;
			document.images['little'].src=tumb[current].src;
	}
}

function prevPhoto()
{
	if (current > 1)
	{
		current--;
		document.images['little'].src=tumb[current].src;
	}
}
function openCurrent()
{
	myWin=open(bigphoto[current], "displayWindow", "width=550,height=430,status=no,toolbar=no,menubar=no,resizable=yes");
}
