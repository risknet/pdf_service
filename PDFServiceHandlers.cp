using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnotics;
using System.Drawing.Printing;
using System.Runtime.InteropServices;
using Microsoft.Win32;
using iTextSharp.text;
using iTextSharp.text.pdf;

namespace Risknet.Services 
{
	static class PDFServiceHandlers
	{
		// merge multipe PDF file inton one single file, add the page number to footer section
		public static void PDF_MergeFiles(string targetFile, string[] sourceFiles, int pageFrom = 1)
		{
			try
			{
				int fileIndex = 0;
				int currentPageNumber = 0;

				// create a reader
				PdfReader reader = new PdfReader(sourceFiles[fileIndex]);
				// get total number of pages
				int totalPagesInFile = reader.NumberOfPages;

				// create a document object
				Document document = new Document(reader.GetPageSizeWithRotation(1));

				// create a writer that listens to the document
				PDFEventHandlers pdfEventHandlers = new PDFEventHandlers();
				pdfEventHandlers.whichPageToStartFrom = pageFrom;

				PdfWriter writer = PdfWriter.GetInstance(document, new FileStream(targetFile, FileMode.Create));
				writer.PageEvent = pdfEventHandlers;

				// open the document
				document.Open();
				PdfContentByte cb = writer.DirectContent;
				PdfImportedPage page;
				int rotation;

				// add a content
				while (fileIndex < sourceFiles.Length)
				{
					int pageNumber = 0;
					while (pageNumber < totalPagesInFile)
					{
						pageNumber++;
						// set current page number to the merged pdf file
						currentPageNumber++;
						PdfPageLabels pageLabels = new PdfPageLabels();
						pageLabels.AddPageLabel(1, PdfPageLabels.DECIMAL_ARABIC_NUMERALS);

						document.SetPageSize(reader.GetPageSizeWithRotation(pageNumber));
						document.NewPage();
						page = writer.GetImportedPage(reader, pageNumber);

						rotation = reader.GetPageRotation(pageNumber);
						if (rotation == 90 || rotation == 270)
						{
							cb.AddTemplate(page, 0, -1f, 1f, 0, 0, reader.GetPageSizeWithRotation(pageNumber).Height);
						}
						else 
						{
							cb.AddTemplate(page, 1f, 0, 0, 1f, 0, 0);
						}
					}
					fileIndex++;
					if (fileIndex < sourceFiles.Length)
					{
						reader = new PdfReader(sourceFiles[fileIndex]);
						totaPagesInFile = reader.NumberOfPages;
					}
				}
				document.Close();
			}
			catch (Excepton e)
			{
				string strOb = e.Message;
				throw e;
			}
		}

		// returns a total page number of a given PDF file name
		public static int PDF_CountPageNumber(string fileName)
		{
			PdfReader reader = new PdfReader(fileName);
			return reader.NumberOfPages;
		}

		// make one single pdf file using given source files (PDFs)
		public static void ProducePDFBookOfReports(string targetFile, string[] sourceFiles, int pageFrom)
		{
			try
			{
				PDF_MergeFiles(targetFile, sourceFiles, pageFrom);
			}
			catch (Exception e)
			{
				throw e;
			}
		}
	}
}
