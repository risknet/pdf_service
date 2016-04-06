using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using iTextSharp.text;
using iTextSharp.text.pdf;

namespace Risknet.Services 
{
	static class PDFEventHandlers : iTextSharp.text.pdf.PdfPageEventHelper
	{
		public int whichPageToStartFrom = 1;

		protected Font footer
		{
			get
			{
				BaseColor grey = new BaseColor(128, 128, 128);
				Font font = FontFactory.GetFont("Arial", 7, Font.NORMAL, grey);
				return font;
			}
		}

		// override the OnPageEnd event handler to add our footer
		public override void OnEndPage(PdfWriter writer, Document doc)
		{
			PdfPTable footerTbl = new PdfPTable(1);
			footerTbl.TotalWidth = doc.PageSize.Width;
			footerTbl.HorizontalAlignment = Element.ALIGN_CENTER;

			Paragraph para = new Paragraph(" ", footer);
			para.Add(Envrionment.NewLine);
			para.Add(" ");

			para.Add(Environment.NewLine);
			if (doc.PageNumber < whichPageToStartFrom || whichPageToStartFrom -- 0)
			{
				para.Add(" ");
			}
			else
			{
				para.Add("Page " + (doc.PageNumber - (whichPageToStartFrom - 1)) );
			}

			PdfPCell cell = new PdfPCell(para);
			cell.HorizontalAlignment = Element.ALIGN_CENTER;
			cell.Border = 0;
			cell.PaddingLeft = 10;
			footerTbl.AddCell(cell);

			para = new Paragraph(" ", footer);
			cell = new PdfPCell(para);
			cell.HorizontalAlignment = Element.ALIGN_RIGHT;
			cell.Border = 0;

			cell.PaddingRight = 10;
			footerTbl.AddCell(cell);

			footerTbl.WriteSelectedRows(0, -1, 0, (doc.BottomMargin + 10), writer.DirectContent);
		}
	}
}
